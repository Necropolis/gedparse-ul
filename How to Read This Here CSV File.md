# How to Read This Here CSV File

Answer: *very carefully*.

The CSV file is the composite of many fields from all the records from the files `SRSUR1.GED` and `SRSUR2.GED`; these were concatenated into a single GEDCOM, `SRSUR.GED`, which were washed through a C++ GEDCOM driver and inserted into a Mongo Database. The Mongo Database was queried to determine some basic characteristics about the data set, from which point the C++ GEDCOM driver's internal data structures were coalesced. The CSV file represents all the kinds of records extant in `SRSUR.GED` as a flat structure. Because of this there are identically named fields which correspond to different parent "objects" based on their order in the record. Additionally, there are many blank (`NULL`) fields. The following list shows the field names, as well as using a multi-level list to show the relationship between those fields and their parent "objects." List items starting with `code-format text` connote a literal field; list items starting with **bold text** do not exist in the CSV file except as a kind of imaginary sub-group. From left to right, the fields are:

1. `type` The record type - either `INDI` or `FAM`.
2. **Name**
	1. `given_names` A space-separated list of given names.
	2. `surname`
	3. `standardised given names` Because of the nature of the data structure, these will always be blank.
	4. `standardised surnames` Because of the nature of the data structure, these will always be blank.
3. **Father**
	1. `given_names` A space-separated list of given names.
	2. `surname`
	3. `standardised given names` Because of the nature of the data structure, these will always be blank.
	4. `standardised surnames` Because of the nature of the data structure, these will always be blank.
4. **Mother**
	1. `given_names` A space-separated list of given names.
	2. `surname`
	3. `standardised given names` Because of the nature of the data structure, these will always be blank.
	4. `standardised surnames` Because of the nature of the data structure, these will always be blank.
5. `gender` Usually either `M` or `F`, though don't count on it.
6. **Marriage**
	1. **Place**
		1. `countyCode`
		2. `country`
		3. `county`
		4. `town`
		5. `borough`
	2. **Date** Note that dates don't always make sense; there is at least one date which has a day and year, but no month.
		1. `day`
		2. `month`
		3. `year`
7. **Spouse**
	1. **Name**
		1. `given_names`
		2. `surname`
		3. `standardised given names` A space-separated list of standardised given names. *This one will actually have stuff in it from time to time!*
		4. `standardised surnames` A space-separated list of standardised given names. *This one will actually have stuff in it from time to time!*
	2. `standardised given names` One would think that these would be in § 7.1, but it isn't.
	3. `standardised surnames` One would think that these would be in § 7.1, but it isn't.
8. **Event**
	1. `type` The type of event, eg `CM` (for male christening).
	2. **Date** Note that dates don't always make sense; there is at least one date which has a day and year, but no month.
		1. `day`
		2. `month`
		3. `year`
	3. **Place**
		1. `countyCode`
		2. `country`
		3. `county`
		4. `town`
		5. `borough`
9. `misc` There's occassionally some miscelleneous notes kicking around here.
10. `batch`


