# Operators

Here we have the currently supported Operators in Symvl. At the Moment we do not have any Postfix-Operators in Symvl. No Problem, they will be added in further Releases.


## Boolean Operators

|Operator  | Usage |
|--|--|
| > | Bigger than, returns true if left is bigger than right Value |
| < | Less than, returns true if the left is less than right Value|
| >=| Bigger than or equals|
| <=| Less than or equals|
|==| Equals, returns true if the left equals the right value|
|~=| Not Equals
|and| logical and Operator / Keyword
|or| logical or Operator / Keyword
|not| logical not Operator / Keyword


## Binary Operators

> Binary Operator execute given Operation between left and right Side. Both Sides have to be a Number-Value. Symvl will pay attention of the given precedence of Operators.

|Operator  | Usage |
|--|--|
|\+| Add left and right side
|\-| Sub left and right side
|\*| Multiply left and right side
|"\"| Divide left and right side
|\%| Modular
|\^| Exponent


## Misc Operators / Indicators

|Operator  | Usage |
|--|--|
|\#| This Operator returns the length of an String or Array.
|. .| The "concatenate" Operator, concatenate two string Values
|[ ]| The Index Indicator will point to a specific Index of an Array
|{ }| The Array Indicator will initialize an Array on a Variable or Object and can be filled with multiple other Values, Tables, Objects.
|\" and \'| At one side the double- and the other side the single-Quote. Both are initializing a String
|( )| Last but not least the left and right Parentheses which will either set the precedence of Operations, call Functions or initialize Parameters of a Function-header.


[Next Chapter, Basics of Symvl](https://github.com/BlackFoX1991/Symvl/tree/main/docs/basics.md)
