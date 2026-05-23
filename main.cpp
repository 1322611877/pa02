// Winter'24
// Instructor: Diba Mirza
// Student name: Jialu XING
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);

    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    // Create an object of a STL data-structure to store all the movies
    MoviesFunc m;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        m.addMovie(movieName, movieRating);
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
        m.printAllSorted();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    //struct to store prefix and certain movie
struct BestResult {
        string prefix;
        Movie best;
    };

    vector<BestResult> bestResults;

    for (string& prefix : prefixes) {
        //copy function
        vector<Movie> matches = m.findByprefix(prefix);

        if (matches.empty()) {
            // Spec: no blank line after this message
            cout << "No movies found with prefix " << prefix << "\n";
        } else {
            //prefix block
            for (Movie& mm : matches) {
                cout << mm.name << ", " << fixed << setprecision(1) << mm.rating << "\n";
            }
            cout << "\n";
            //The first found result will be the best movie
            bestResults.push_back({prefix, matches[0]});
        }
    }

    for ( BestResult& r : bestResults) {
        cout << "Best movie with prefix " << r.prefix << " is: "
             << r.best.name << " with rating "
             << fixed << setprecision(1) << r.best.rating << "\n";
    }
    return 0;
}

/*
 *dataset size = n
 *prefix number = m
 *maximum character in a movie name = l(length)
 *maximum movie number that share one prefix = k
 *
 *the basic data structure to store movie is map
 *
 *time complexity:
 *1. building map O(l * nlogn)
 *2. find certain prefix O(l*logn) repeat m times O(m* l*logn)
 *3. Iterate k matching movies ->compare again O(k*logk)
 *4. sort k movies by rating O(k*l*logk)
 *
 *for general situation k<<n
 *total time complexity = O(m * l * logn)
 *
 *Space complexity
 *map storage O(n*l)
 *prefix storage O(k*l)
 *overall storage O(n*l) (k<<n)
 *
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}