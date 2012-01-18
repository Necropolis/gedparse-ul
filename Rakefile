require 'rake/clean'
require 'rake/loaders/makefile'

import '.depend.mf'

APPLICATION = 'gedparse-ul'
BOOST_PATH = ''

CC = 'clang++'
LD = CC

CFLAGS = [
  '-Imongo',
  '-DDEBUG'
].join(' ')

LIBS = [
  "-lboost_program_options-mt",
  "-lboost_thread-mt",
  "-lboost_filesystem-mt",
  "-lboost_system-mt",
  "-Lmongo -lmongoclient"
].join(' ')

CPP_SOURCES = FileList['src/*.cpp']
O_FILES = CPP_SOURCES.sub(/\.cpp$/, '.o')

file APPLICATION => O_FILES do |t|
  sh "#{LD} #{LIBS} #{O_FILES} -o #{t.name}"
end

file '.depend.mf' do
  sh "makedepend -f- -- #{CFLAGS} -- #{CPP_SOURCES} > .depend.mf"
end

CPP_SOURCES.each do |src|
  file src.ext(".o") => src
end

rule '.o' => ['.cpp'] do |t|
  sh "#{CC} #{t.source} #{CFLAGS} -c -o #{t.name}"
end

CLEAN.include("**/*.o")
CLOBBER.include(APPLICATION)

desc "compile the tool"
task :compile => APPLICATION

task :default => :compile
