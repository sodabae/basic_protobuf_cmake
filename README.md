# Commands to compile the code:
mkdir build  
cd build  
cmake ..  
cmake --build .  

This expects protoc is already installed and ready to use. It creates an app 'address_book_app'

# Doxygen
Source code contains doxygen style comments. Can create the doxygen HTML output by doing:  
doxygen Doxyfile

To generate a PDF file, use the command:  
cd docs/latex && make

## From container:
The same commands can be executed using a docker container using commands (from the same directory as the Doxyfile) such as:  
docker run --rm -v "$(pwd):/workspace" doxygen doxygen Doxyfile  
docker run --rm -v "$(pwd):/workspace" doxygen bash -c "cd docs/latex && make"

## Output Files
Doxygen will create the following files:  
HTML: docs/html/index.html  
PDF : docs/latex/refman.pdf

# Tests
Google tests can by run by executing the test file:
`./build/tests/address_book_tests`

# Coverage
The address_book.cpp source code has had coverage added to it. To compile for coverage, use the following commands:
mkdir build  
cd build  
cmake -DENABLE_COVERAGE=ON ..  
cmake --build .

## Confirming which files have coverage
Confirmation of coverage being applied to files can be done in 2 ways:
1. Check the build/compile_commands.json file. The files that are compiled (not linked) with --coverage will have coverage applied
1. Use the command `find -name "*.gcno"` to see which files were compiled with coverage. After running the executable code (executable file, tests, etc), *.gcda files will appear. You can also check for these files are the code is executed by using the command  `find -name "*.gcda"`

## Generating the coverage results. Run the following from the build directory:
lcov --capture --directory . --output-file coverage.info  
lcov --remove coverage.info '/usr/*' '*/generated/*' '*/tests/*' --output-file coverage.cleaned.info  
genhtml coverage.cleaned.info --output-directory coverage_html
