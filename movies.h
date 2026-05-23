#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

struct Movie {
    string name;
    double rating;
};

class MoviesFunc {
    public:
    //fundamental function -> add movie
    void addMovie(string &name, double rating);
    //print all movie in name order
    void printAllSorted();
    //return all movies start with given prefix
    vector<Movie> findByprefix(string &prefix);
    private:
    map<string, double> movies_;
};
