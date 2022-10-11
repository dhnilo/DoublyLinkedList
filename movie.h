//Header file for the struct Movie
#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Movie {
private:

public:
  string title;
  string director_name;
  int release_year;

  Movie() {
    this->title = "";
    this->director_name = "";
    this->release_year = 0;
  }

  Movie(string t, string dn, int ry) {
    this->title = t;
    this->director_name = dn;
    this->release_year = ry;
  }

  Movie(const Movie & obj) {
    this->title = obj.title;
    this->director_name = obj.director_name;
    this->release_year = obj.release_year;
  }

  string to_string() {
    string rY = std::to_string(release_year);
    string movie = this->title + ", " + this->director_name + ", " + rY;
    return movie;
  }

  bool operator==(const Movie &obj) const {
    if (this->title == obj.title && this->director_name == obj.director_name && this->release_year == obj.release_year)
      return true;
    else
      return false;
  }
};

// overloading cout<< in order to display Movie object
ostream & operator << (ostream &out, const Movie &m) {
  return (out << "Title: " << m.title << "\nDirector Name: " << m.director_name << "\nRelease Year: " << m.release_year);
}
#endif
