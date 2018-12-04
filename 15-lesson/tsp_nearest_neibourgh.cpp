/*
In this assignment we will revisit an old friend, the traveling salesman problem (TSP). This week you will implement a heuristic for the TSP, rather than an exact algorithm, and as a result will be able to handle much larger problem sizes. Here is a data file describing a TSP instance (original source: http://www.math.uwaterloo.ca/tsp/world/bm33708.tsp).
nn.txt

The first line indicates the number of cities. Each city is a point in the plane, and each subsequent line indicates the x- and y-coordinates of a single city.

The distance between two cities is defined as the Euclidean distance --- that is, two cities at locations (x,y)(x,y)(x,y) and (z,w)(z,w)(z,w) have distance (x−z)2+(y−w)2\sqrt{(x-z)^2 + (y-w)^2}(x−z)2+(y−w)2

​ between them.

You should implement the nearest neighbor heuristic:

    Start the tour at the first city.
    Repeatedly visit the closest city that the tour hasn't visited yet. In case of a tie, go to the closest city with the lowest index. For example, if both the third and fifth cities have the same distance from the first city (and are closer than any other city), then the tour should begin by going from the first city to the third city.
    Once every city has been visited exactly once, return to the first city to complete the tour.

In the box below, enter the cost of the traveling salesman tour computed by the nearest neighbor heuristic for this instance, rounded down to the nearest integer.

[Hint: when constructing the tour, you might find it simpler to work with squared Euclidean distances (i.e., the formula above but without the square root) than Euclidean distances. But don't forget to report the length of the tour in terms of standard Euclidean distance.] 
 
 */
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>

namespace mirazabal
{

	template <typename T, typename TIter = decltype(std::begin(std::declval<T>())), typename = decltype(std::end(std::declval<T>()))>
		constexpr auto enumerate(T && iterable)
		{
			struct iterator
			{
				size_t i;
				TIter iter;
				bool operator != (const iterator & other) const { return iter != other.iter; }
				void operator ++ () { ++i; ++iter; }
				auto operator * () const { return std::tie(i, *iter); }
			};
			struct iterable_wrapper
			{
				T iterable;
				auto begin() { return iterator{ 0, std::begin(iterable) }; }
				auto end() { return iterator{ 0, std::end(iterable) }; }
			};
			return iterable_wrapper{ std::forward<T>(iterable) };
		}


	struct City
	{
		int64_t id_;
		double xCoord_;
		double yCoord_;
		bool visited_;
		City(int64_t id, double x, double y) : id_{id}, xCoord_{x}, yCoord_{y}, visited_{false}
		{

		}

	};

	static double euclidianDistance(City const& c1, City const& c2)
	{
		double first = std::pow(c1.xCoord_ - c2.xCoord_,2);
		double second = std::pow(c1.yCoord_ - c2.yCoord_,2);
		return std::pow(first + second,0.5);
	}

	std::vector<City> fillVectorCities(const char* filePath)
	{
		std::ifstream ifstr(filePath);
		std::string str;
		std::getline(ifstr,str);
		std::istringstream iss(str);
		int32_t numCities;
		iss >> numCities;
		std::vector<City> vCities;
		vCities.reserve(numCities);
		while(std::getline(ifstr,str)){
			std::istringstream iss(str);
			int64_t id;
			double x,y;
			iss >> id >> x >> y;
			vCities.emplace_back(City(id,x,y));	
		}
		return vCities;
	}


	int64_t find_next_nearest_city(std::vector<City> const& cities, int64_t IdxActualCity, double& tspDistance)
	{
		double minDistance = std::numeric_limits<double>::max();
		int64_t nextIdx = std::numeric_limits<int64_t>::max();
		for(auto [i,c] : enumerate(cities)){
			if( IdxActualCity == i || c.visited_ == true) 
				continue;

			double distance = euclidianDistance(cities[IdxActualCity], c);
			if(distance < minDistance){
				minDistance = distance;
				nextIdx = i;
			} else if(distance == minDistance && i < nextIdx){
				nextIdx = i;
			}
		}
		tspDistance += minDistance;
		
		std::cout << "tspDistance  = " << std::setprecision(10) << tspDistance << '\n';
		std::cout << "minDistance  = " <<  minDistance << '\n';
		std::cout << "nextIdx  = " <<  nextIdx << '\n';

		return nextIdx;
	}

	double tsp_nearest_neibourgh(int64_t indexFirstCity, std::vector<City>& cities)
	{
		int counterCitiesVisited = 1;
		double tspDistance = 0;	
		int IdxNextCity =  indexFirstCity;
		while(counterCitiesVisited < cities.size()){
			cities[IdxNextCity].visited_ = true;
			IdxNextCity = find_next_nearest_city(cities, IdxNextCity, tspDistance);
			++counterCitiesVisited; 
			std::cout << "cities visited so far = " <<  counterCitiesVisited << '\n';
		}
		double returnDist =  euclidianDistance( cities[indexFirstCity], cities[IdxNextCity]);
		tspDistance += returnDist;
		return tspDistance;
	}

};


int main()
{
	auto cities = mirazabal::fillVectorCities("nn.txt");
	std::cout <<  std::setprecision(10) << mirazabal::tsp_nearest_neibourgh(0, cities) << '\n';
	return 0;
}
