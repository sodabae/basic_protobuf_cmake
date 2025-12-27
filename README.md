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