Metafile importer instructions

The Metafile importer can be run via command line with the command metaimp
running metaimp in the project root directory will automatically comb all files 
and folders in the res directory and prompt you to input any info for any file
that lacks a Metafile

Options:
    -f [path]:  rather than recursively searching the system, the importer will attempt
                to locate the file at the given path and only create a metafile for
                that file. if the path leads to a directory, the importer will look at
                all files in that directory without metafiles. If multiple -f options
                are used, the importer will search each file
    -r          For use with the -f option. Tells the program to search recursively still, but with
                the folder(s) specified by -f as the root directory
    -a:         the metafile importer will run throught ALL files (or all files in the
                given director(ies) if used with the -f option) and prompt metafile data
                for each. this may take a while with a significant number of metafiles
    -o          reads metafiles into command line, rather than prompting you to make new ones