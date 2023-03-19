#include "Lex.h"
#include "../VM/State.h"
#include "../S_Exception/Exception.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>

namespace
{
    const char *keyword[] = {
        "and", "break", "do", "else", "elseif", "end",
        "false", "for", "function", "if", "in",
        "local", "nil", "not", "or", "repeat",
        "return", "then", "true", "until", "while"
    };

    bool IsKeyWord(const std::string& name, int *token)
    {
        assert(token);
        auto result = std::equal_range(keyword, keyword + sizeof(keyword) / sizeof(keyword[0]),
                                       name.c_str(), [](const char *left, const char *right) {
                                           return strcmp(left, right) < 0;
                                       });
        if (result.first == result.second)
            return false;

        *token = result.first - keyword + symvl::Token_And;
        return true;
    }

    inline bool IsHexChar(int c)
    {
        return (c >= '0' && c <= '9') ||
               (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F');
    }
} // namespace

namespace symvl
{
#define RETURN_NORMAL_TOKEN_DETAIL(detail, token)               \
    do {                                                        \
        detail->token_ = token;                                 \
        detail->line_ = line_;                                  \
        detail->column_ = column_;                              \
        detail->module_ = module_;                              \
        return token;                                           \
    } while (0)

#define RETURN_NUMBER_TOKEN_DETAIL(detail, number)              \
    do {                                                        \
        detail->number_ = number;                               \
        RETURN_NORMAL_TOKEN_DETAIL(detail, Token_Number);       \
    } while (0)

#define RETURN_TOKEN_DETAIL(detail, string, token)              \
    do {                                                        \
        detail->str_ = state_->GetString(string);               \
        RETURN_NORMAL_TOKEN_DETAIL(detail, token);              \
    } while (0)

#define SET_EOF_TOKEN_DETAIL(detail)                            \
    do {                                                        \
        detail->str_ = nullptr;                                 \
        detail->token_ = Token_EOF;                             \
        detail->line_ = line_;                                  \
        detail->column_ = column_;                              \
        detail->module_ = module_;                              \
    } while (0)

    Lexer::Lexer(State *state, String *module, CharInStream in)
        : state_(state),
          module_(module),
          in_stream_(in),
          current_(EOF),
          line_(1),
          column_(0)
    {
    }

    int Lexer::GetToken(TokenDetail *detail)
    {
        assert(detail);
        SET_EOF_TOKEN_DETAIL(detail);
        if (current_ == EOF)
            current_ = Next();

        while (current_ != EOF)
        {
            switch (current_) {
            case ' ': case '\t': case '\v': case '\f':
                current_ = Next();
                break;
            case '\r': case '\n':
                LexNewLine();
                break;
            case '-':
                {
                    int next = Next();
                    if (next == '-')
                        LexComment();
                    else
                    {
                        current_ = next;
                        RETURN_NORMAL_TOKEN_DETAIL(detail, '-');
                    }
                }
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                return LexNumber(detail);
            case '+': case '*': case '/': case '%': case '^':
            case '#': case '(': case ')': case '{': case '}':
            case ']': case ';': case ':': case ',':
                {
                    int token = current_;
                    current_ = Next();
                    RETURN_NORMAL_TOKEN_DETAIL(detail, token);
                }
                break;
            case '.':
                {
                    int next = Next();
                    if (next == '.')
                    {
                        int pre_next = Next();
                        if (pre_next == '.')
                        {
                            current_ = Next();
                            RETURN_NORMAL_TOKEN_DETAIL(detail, Token_VarArg);
                        }
                        else
                        {
                            current_ = pre_next;
                            RETURN_NORMAL_TOKEN_DETAIL(detail, Token_Concat);
                        }
                    }
                    else if (isdigit(next))
                    {
                        token_buffer_.clear();
                        token_buffer_.push_back(current_);
                        current_ = next;
                        return LexNumberXFractional(detail, false, true,
                                                    [](int c) { return isdigit(c) != 0; },
                                                    [](int c) { return c == 'e' || c == 'E'; });
                    }
                    else
                    {
                        current_ = next;
                        RETURN_NORMAL_TOKEN_DETAIL(detail, '.');
                    }
                }
                break;
            case '~':
                {
                    int next = Next();
                    if (next != '=')
                        throw LexException(module_->GetCStr(),
                                line_, column_, "expect '=' after '~'");
                    current_ = Next();
                    RETURN_NORMAL_TOKEN_DETAIL(detail, Token_NotEqual);
                }
                break;
            case '=':
                return LexXEqual(detail, Token_Equal);
            case '>':
                return LexXEqual(detail, Token_GreaterEqual);
            case '<':
                return LexXEqual(detail, Token_LessEqual);
            case '[':
                {
                    current_ = Next();
                    if (current_ == '[' || current_ == '=')
                        return LexMultiLineString(detail);
                    else
                        RETURN_NORMAL_TOKEN_DETAIL(detail, '[');
                }
                break;
            case '\'': case '"':
                return LexSingleLineString(detail);
            default:
                return LexId(detail);
            }
        }

        return Token_EOF;
    }

    void Lexer::LexNewLine()
    {
        int next = Next();
        if ((next == '\r' || next == '\n') && next != current_)
            current_ = Next();
        else
            current_ = next;
        ++line_;
        column_ = 0;
    }

    void Lexer::LexComment()
    {
        current_ = Next();
        if (current_ == '[')
        {
            current_ = Next();
            if (current_ == '[')
                LexMultiLineComment();
            else
                LexSingleLineComment();
        }
        else
            LexSingleLineComment();
    }

    void Lexer::LexMultiLineComment()
    {
        bool is_comment_end = false;
        while (!is_comment_end)
        {
            if (current_ == ']')
            {
                current_ = Next();
                if (current_ == ']')
                {
                    is_comment_end = true;
                    current_ = Next();
                }
            }
            else if (current_ == EOF)
            {
                // uncompleted multi-line comment
                throw LexException(module_->GetCStr(), line_, column_,
                        "expect complete multi-line comment before <eof>.");
            }
            else if (current_ == '\r' || current_ == '\n')
            {
                LexNewLine();
            }
            else
            {
                current_ = Next();
            }
        }
    }

    void Lexer::LexSingleLineComment()
    {
        while (current_ != '\r' && current_ != '\n' && current_ != EOF)
            current_ = Next();
    }

    int Lexer::LexNumber(TokenDetail *detail)
    {
        bool integer_part = false;
        token_buffer_.clear();
        if (current_ == '0')
        {
            int next = Next();
            if (next == 'x' || next == 'X')
            {
                token_buffer_.push_back(current_);
                token_buffer_.push_back(next);
                current_ = Next();

                return LexNumberX(detail, false, IsHexChar,
                                  [](int c) { return c == 'p' || c == 'P'; });
            }
            else
            {
                token_buffer_.push_back(current_);
                current_ = next;
                integer_part = true;
            }
        }

        return LexNumberX(detail, integer_part,
                          [](int c) { return isdigit(c) != 0; },
                          [](int c) { return c == 'e' || c == 'E'; });
    }

    int Lexer::LexNumberX(TokenDetail *detail, bool integer_part,
                          const std::function<bool (int)> &is_number_char,
                          const std::function<bool (int)> &is_exponent)
    {
        while (is_number_char(current_))
        {
            token_buffer_.push_back(current_);
            current_ = Next();
            integer_part = true;
        }

        bool point = false;
        if (current_ == '.')
        {
            token_buffer_.push_back(current_);
            current_ = Next();
            point = true;
        }

        return LexNumberXFractional(detail, integer_part, point,
                                    is_number_char, is_exponent);
    }

    int Lexer::LexNumberXFractional(TokenDetail *detail,
                                    bool integer_part, bool point,
                                    const std::function<bool (int)> &is_number_char,
                                    const std::function<bool (int)> &is_exponent)
    {
        bool fractional_part = false;
        while (is_number_char(current_))
        {
            token_buffer_.push_back(current_);
            current_ = Next();
            fractional_part = true;
        }

        if (point && !integer_part && !fractional_part)
            throw LexException(module_->GetCStr(), line_, column_,
                    "unexpect '.'");
        else if (!point && !integer_part && !fractional_part)
            throw LexException(module_->GetCStr(), line_, column_,
                    "unexpect incomplete number '", token_buffer_, "'");

        if (is_exponent(current_))
        {
            token_buffer_.push_back(current_);
            current_ = Next();
            if (current_ == '-' || current_ == '+')
            {
                token_buffer_.push_back(current_);
                current_ = Next();
            }

            if (!isdigit(current_))
                throw LexException(module_->GetCStr(), line_, column_,
                        "expect exponent after '", token_buffer_, "'");

            while (isdigit(current_))
            {
                token_buffer_.push_back(current_);
                current_ = Next();
            }
        }

        double number = strtod(token_buffer_.c_str(), nullptr);
        RETURN_NUMBER_TOKEN_DETAIL(detail, number);
    }

    int Lexer::LexXEqual(TokenDetail *detail, int equal_token)
    {
        int token = current_;

        int next = Next();
        if (next == '=')
        {
            current_ = Next();
            RETURN_NORMAL_TOKEN_DETAIL(detail, equal_token);
        }
        else
        {
            current_ = next;
            RETURN_NORMAL_TOKEN_DETAIL(detail, token);
        }
    }

    int Lexer::LexMultiLineString(TokenDetail *detail)
    {
        int equals = 0;
        while (current_ == '=')
        {
            ++equals;
            current_ = Next();
        }

        if (current_ != '[')
            throw LexException(module_->GetCStr(), line_, column_,
                    "incomplete multi-line string at '", token_buffer_, "'");

        current_ = Next();
        token_buffer_.clear();

        if (current_ == '\r' || current_ == '\n')
        {
            LexNewLine();
            if (equals == 0)    // "[[]]" keeps first '\n'
                token_buffer_.push_back('\n');
        }

        while (current_ != EOF)
        {
            if (current_ == ']')
            {
                current_ = Next();
                int i = 0;
                for (; i < equals; ++i, current_ = Next())
                {
                    if (current_ != '=')
                        break;
                }

                if (i == equals && current_ == ']')
                {
                    current_ = Next();
                    RETURN_TOKEN_DETAIL(detail, token_buffer_, Token_String);
                }
                else
                {
                    token_buffer_.push_back(']');
                    token_buffer_.append(i, '=');
                }
            }
            else if (current_ == '\r' || current_ == '\n')
            {
                LexNewLine();
                token_buffer_.push_back('\n');
            }
            else
            {
                token_buffer_.push_back(current_);
                current_ = Next();
            }
        }

        throw LexException(module_->GetCStr(), line_, column_,
                "incomplete multi-line string at <eof>");
    }

    int Lexer::LexSingleLineString(TokenDetail *detail)
    {
        int quote = current_;
        current_ = Next();
        token_buffer_.clear();

        while (current_ != quote)
        {
            if (current_ == EOF)
                throw LexException(module_->GetCStr(), line_, column_,
                        "incomplete string at <eof>");

            if (current_ == '\r' || current_ == '\n')
                throw LexException(module_->GetCStr(), line_, column_,
                        "incomplete string at this line");

            LexStringChar();
        }

        current_ = Next();
        RETURN_TOKEN_DETAIL(detail, token_buffer_, Token_String);
    }

    void Lexer::LexStringChar()
    {
        if (current_ == '\\')
        {
            current_ = Next();
            if (current_ == 'a')
                token_buffer_.push_back('\a');
            else if (current_ == 'b')
                token_buffer_.push_back('\b');
            else if (current_ == 'f')
                token_buffer_.push_back('\f');
            else if (current_ == 'n')
                token_buffer_.push_back('\n');
            else if (current_ == 'r')
                token_buffer_.push_back('\r');
            else if (current_ == 't')
                token_buffer_.push_back('\t');
            else if (current_ == 'v')
                token_buffer_.push_back('\v');
            else if (current_ == '\\')
                token_buffer_.push_back('\\');
            else if (current_ == '"')
                token_buffer_.push_back('"');
            else if (current_ == '\'')
                token_buffer_.push_back('\'');
            else if (current_ == 'x')
            {
                current_ = Next();
                char hex[3] = { 0 };
                int i = 0;
                for (; i < 2 && IsHexChar(current_); ++i, current_ = Next())
                    hex[i] = current_;
                if (i == 0)
                    throw LexException(module_->GetCStr(), line_, column_,
                            "unexpect character after '\\x'");
                token_buffer_.push_back(static_cast<char>(strtoul(hex, 0, 16)));
                return ;
            }
            else if (isdigit(current_))
            {
                char oct[4] = { 0 };
                for (int i = 0; i < 3 && isdigit(current_); ++i, current_ = Next())
                    oct[i] = current_;
                token_buffer_.push_back(static_cast<char>(strtoul(oct, 0, 8)));
                return ;
            }
            else
                throw LexException(module_->GetCStr(), line_, column_,
                        "unexpect character after '\\'");
        }
        else
        {
            token_buffer_.push_back(current_);
        }

        current_ = Next();
    }

    int Lexer::LexId(TokenDetail *detail)
    {
        if (!isalpha(current_) && current_ != '_')
            throw LexException(module_->GetCStr(),
                    line_, column_, "unexpect character");

        token_buffer_.clear();
        token_buffer_.push_back(current_);
        current_ = Next();

        while (isalnum(current_) || current_ == '_')
        {
            token_buffer_.push_back(current_);
            current_ = Next();
        }

        int token = 0;
        if (!IsKeyWord(token_buffer_, &token))
            token = Token_Id;
        RETURN_TOKEN_DETAIL(detail, token_buffer_, token);
    }
} // namespace symvl
