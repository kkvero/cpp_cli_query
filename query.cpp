/*
USAGE AND OUTPUT EXAMPLE
$ ./query file01.txt
enter word to look for, or q to quit: object
occurs 2 times on these lines:
(line 2) if the TextQuery object is destroyed before a corresponding QueryResult? In
(line 3) that case, the QueryResult would refer to data in an object that no longer exists.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

struct TextQuery
{
    std::ifstream &infile;
    std::vector<std::string> all_lines;
    std::map<std::string, std::set<int>> word_on_lines;
    std::string word;

    // result data for a particular word
    std::set<int> lines_numbers;
    std::vector<std::string> lines_content;

    TextQuery(std::ifstream &in) : infile(in)
    {
        std::string line;
        int i{0};
        while (getline(infile, line))
        {
            // Populate the vector containing all lines and map that maps each
            // word in text file to a set of line numbers where word appears
            all_lines.push_back(line);
            std::istringstream li(line); // breaks line into words
            while (li >> word)
                word_on_lines[word].insert(i);
            ++i;
        }
    }
    std::pair<std::set<int>, std::vector<std::string>> query(std::string &word)
    {
        if (word_on_lines.find(word) == word_on_lines.end())
        {
            lines_numbers = {};
            lines_content = {};
        }
        else
        {

            // line numbers where word appears
            lines_numbers = word_on_lines[word];

            // populate lines_content with actual lines where word appears
            for (auto &i : lines_numbers)
            {
                lines_content.push_back(all_lines.at(i));
            }
        }
        return {lines_numbers, lines_content};
    }
};

struct QueryResult
{
    void print(std::ostream &stream,
               const std::pair<std::set<int>, std::vector<std::string>> &result)
    {
        if (result.first.size() == 0)
        {
            stream << "Sorry, no such word in file. Try another word." << std::endl;
        }
        else
        {
            stream << "occurs " << result.first.size() << " times on these lines:"
                   << std::endl;
            // Iterate set and vector containers in parallel.
            auto set_it = result.first.begin();
            auto vec_it = result.second.begin();
            while (set_it != result.first.end())
                // +1 to avoid 0-based lines count
                stream << "(line " << *set_it++ + 1 << ") " << *vec_it++ << std::endl;
        }
    }
};

void runQueries(std::ifstream &infile)
{
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile); // store the file and build the query map
    // iterate with the user: prompt for a word to find and print results
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        // stop if we hit end-of-file on the input or if a ’q’ is entered
        if (!(std::cin >> s) || s == "q")
            break;

        // run the query and print the results
        QueryResult qres;
        qres.print(std::cout, tq.query(s));
    }
}

int main(int argc, char **argv)
{
    // Check if filename was given.
    if (argc < 2)
    {
        std::cerr << "Usage: " << *argv << " <input_file>\n";
        return EXIT_FAILURE;
    }
    // Get pointer to the file name.
    auto path_to_file = ++argv;
    // Creates an fstream named "input_file".
    std::ifstream input_file(*path_to_file);
    // Our function takes ifstream type
    runQueries(input_file);
}