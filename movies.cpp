#include "movies.h"
#include <iostream>
#include <iomanip>
#include <vector>


using namespace std;

// void addMovie(string &name, double &rating);
// void printAllMovies();
// vector<Movie> findByprefix(string &prefix);

// map<string, double> movies;

void MoviesFunc::addMovie(string &name, double rating) {
    movies_[name] = rating;
}

void MoviesFunc::printAllSorted() {
    for (auto &mv : movies_) {
        cout <<mv.first << ", " << fixed << setprecision(1) << mv.second << "\n";
    }
}

vector<Movie> MoviesFunc::findByprefix(string &prefix){
    vector<Movie> result;
    if (prefix.empty()) return result;
    //find the first movie matches the prefix
    auto it = movies_.lower_bound(prefix);
    int size = prefix.size();
//IF find the prefix
    while (it != movies_.end()) {
        const string &name = it->first;
        //Two conditions to break the while loop name size < prefix size or doesn't match
        if (name.size() < size || name.compare(0, size, prefix) != 0)
            break;
        result.push_back({name,it->second});
        ++it;
    }
        return result;
    }
