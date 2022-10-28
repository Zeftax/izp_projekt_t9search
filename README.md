# How to use
* Syntax for this command is t9search [query] [parameters]
* It is recommended to feed it a preformatted file using a | or <. Although you can enter contacts manually from tty (warning: you will not be given any prompts)

## Input format
* Input should look like this:
	* Contact name 1
	* Contact number 1
	* Contact name 2
	* Contact name 2
	* ...
	* Contact name n
	* Contact number n
* You cannot skip lines or input needles emptu lines like so:
	* Contact name 1
	* Contact name 2
	* Contact number 2
	* Contact name 3
	* <\n>
	* Contact number 3
* Maximum length of a line is 100 characters. Any characters after the 100 mark will be discarted and not searchable (or displayed).

## Query format
* Please input your query using digits only. You can look for digits in number, or in name.
* Query has to be less than or equal to 100 characters long.
* If you are searching for a name, you can ignore special and white characters.
* Input letters as you would on a normal mobile phone, but do not repeat digits to get to a letter. Quick quide:
	* 0 = 0
	* 1 = 1
	* 2 = 2abcABC
	* 3 = 3defDEF
	* 4 = 4ghiGHI
	* 5 = 5jklJKL
	* 6 = 6mnoMNO
	* 7 = 7pqrsPQRS
	* 8 = 8tuvTUV
	* 9 = 9wxyzWXYZ

# Command line arguments
* -s = skip characters.
	* Allows you to search for characters that are in the  contact in that order, but not necessarily right next to each other. e.g.:
		* Number you are looking for is 458 687 569
		* Query you inputed is 4676
		* Without -s parameter this contact will not be found, because it does not contain this sequence of numbers.
		* With the -s parameter this contact will be found, because all these characters in this order do appear in the number.
* -l = Levenshtein distance
	* Not Implemented Yet
	* How much error is allowed in the input for the match to be still allowed to be positive.

# Error codes
	* Fatal:
		* -1 = Invalid query. Please refer to the query format section of the README.
		* -2 = No argument specified for <parameter>. This parameter is missing a required argument.
		* -3 = Invalid argument. The argument you specified is not valid.
