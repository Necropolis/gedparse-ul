# Misc. GEDCOM Code

The beginning of an unlinked GEDCOM driver - code that can read and emit unlinked GEDCOM data. Due to the Mongo-stuff, it also can emit the GEDCOM data into a BSON format using the Mongo reference emitter.

This mess was all written to facilitate the conversion of some old unlinked GEDCOM files to a MongoDB instance, from where they were sanitized and exported into a CSV. From there another team used another piece of software to convert that to a linked GEDCOM.

This code is very specialized and wasn't intended for heavy re-use without modification.

## C++

A faster, sexier, altogether more better and tastier parser written in C++. It makes use of C++'s awesome `iostream` library, as well as Boost C++.

You'll need the following:

* Clang. I don't bother working with GCC, so your results may vary. This was tested using Apple LLVM 3.0 on Mac OS X 10.7 "Lion" with Xcode 4.2.
* Boost C++. If you're on a Mac, the easiest way to get this is Homebrew; just `brew install boost`.
* Ruby and Rake. I'd suggest using RVM to install Ruby:  
  
    ```
    rvm install 1.9.3
    rvm use --default 1.9.3 # omit the --default if you don't want to use 1.9.3 by default
    gem install rake
    ```
  
    If you want to mess around with the Ruby code, then you'll also want Thor:
  
    ```
    gem install thor
    ```
* Mongo's C++ Driver.
  * Mongo's C++ Driver requires `boost`, `pcre++`, and `scons`. Install those - again, Homebrew is your best bet: `for pkg in boost pcre++ scons; do brew install $pkg; done`.
  * Mongo itself is in a submodule, so once you clone that out using Git's submodule commands all you need to do is run `scons mongoclient` in the `mongo` sub directory to build the client, and then Rake should be good to go.

Use the `Rakefile` to build it:

    rake
    ./gedparse-ul --if=path/to/my/gedcom.ged --db=scots --col=records_low --ro=false
    
## GedcomReader.rb

*Note that this Ruby reader is fundamentally broken.* Please don't use it. It doesn't work reliably, and it eats RAM like there's no freakin tomorrow.

This is a class, `FamilySearch::GEDCOM::Reader`, which is built to parse unlinked GEDCOM files and generate an array of records. Each record is a hash. An example record would be:

	{:type=>"FAM",
	  :sex=>"MS",
	  :spouse=>{:standardised_surname=>"MARTIN", :name=>"/MARTEIN"},
	  :marriage=>
	   {:date=>{:day=>"26", :month=>"Feb", :year=>"1587"},
	    :place=>"Fife, Scotland, Fife, Anstruther Wester"},
	  :misc=>"FR106",
	  :batch=>"M114032"}