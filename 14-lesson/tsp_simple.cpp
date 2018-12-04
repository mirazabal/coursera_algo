#include <algorithm>
#include <cstdint>
#include <complex>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream> 
#include <string>
#include <limits>
#include <vector>

namespace mirazabal
{

struct City
{
	City(double xCoordinate, double yCoordinate) : xCoord_(xCoordinate) , yCoord_(yCoordinate) 
	{
	
	}
	double xCoord_;
	double yCoord_;
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
	while(std::getline(ifstr,str)){
		std::istringstream iss(str);
		double x,y;
		iss >> x >> y;
	  City c(x,y);
		vCities.emplace_back(City(x,y));	
	}
	return vCities;
}

std::vector<std::vector<double>> createGraphFromVec(std::vector<City> const& vecCities)
{
 	constexpr static double distanceFromCityToItself{0};
	const uint32_t numCities = vecCities.size();
	std::vector<std::vector<double>> graphCities(numCities, std::vector<double>(numCities,distanceFromCityToItself));

	for(auto i = 0u; i < vecCities.size()-1; ++i){
		for(auto j = i+1; j < vecCities.size(); ++j){
			if(i == j) continue;
			
			double distance = euclidianDistance(vecCities[i],vecCities[j]);
			graphCities[i][j] = distance;
			graphCities[j][i] = distance;
		}
	}
	return graphCities;
}

std::vector<std::vector<double>> createGraphFromFile(const char* filePath)
{
	auto vecCities = fillVectorCities(filePath);
	return createGraphFromVec(vecCities);
}

void subset(std::vector<uint32_t> const& data, uint32_t index, uint32_t cardinalityLeft, std::vector<uint32_t> & helper, std::vector<std::vector<uint32_t>> & retVec)
{
	if(cardinalityLeft == 0 )
	{
 		retVec.emplace_back(helper);
		return;
	}

	for(auto i  = index; i < data.size(); ++i){
		helper.push_back(data[i]);
		subset(data, i+1, cardinalityLeft-1, helper, retVec);
		helper.pop_back();
	}

}

std::vector<uint32_t> subsetWithout(std::vector<uint32_t> const& subset, uint32_t val)
{
	std::vector<uint32_t> smallerSubset = subset;
	smallerSubset.erase(std::remove(smallerSubset.begin(), smallerSubset.end(), val), smallerSubset.end());
	return smallerSubset;
}


std::vector<std::vector<uint32_t>> getAllSubsets(uint32_t subsetSize, uint32_t numElem)
{
	std::vector<uint32_t> v(numElem);
	std::iota(std::begin(v),std::end(v), 0);

	std::vector<uint32_t> helper;
	std::vector<std::vector<uint32_t>> retVal;
	subset(v,0,subsetSize,helper,retVal);
	
	return retVal;
}

std::map<uint32_t,std::map< std::vector<uint32_t> , double>> arr;
//      -- cityIdx -----------------   subset   -------- cost

void generate_all_costs(uint32_t subsetSize, std::vector<std::vector<double>> const& graph)
{
	auto allSubsets = getAllSubsets(subsetSize, graph.size());
	for(auto const& subset : allSubsets){
		if(std::find(std::begin(subset), std::end(subset),0) == std::end(subset) ) continue;
		for(auto cityIdx : subset ){
			if(cityIdx == 0) continue;
			
			double min = std::numeric_limits<double>::max();
			for(auto secondCityIdx : subset){
				if(secondCityIdx == cityIdx) continue;
				
				auto& m2 = arr[secondCityIdx];
				auto copySubset = subsetWithout(subset,cityIdx);
				if(m2.find(copySubset) == std::end(m2) )
					continue;
				auto subsetCost = m2[copySubset]; 	

				if(min > subsetCost + graph[secondCityIdx][cityIdx])
					min = subsetCost + graph[secondCityIdx][cityIdx];
			}
			auto& m = arr[cityIdx];
			m[subset] = min;
		}	
	}
}

void base_case()
{
	auto& m = arr[0];
	std::vector<uint32_t> v;
	v.push_back(0);
	m[v] = 0;
}

double tsp_dynamic(std::vector<std::vector<double>> const& graph)
{
	base_case();
	for(uint32_t m = 2; m != graph.size() +1; ++m){ //size of the subset
			generate_all_costs(m, graph);
	}	

	double min = std::numeric_limits<double>::max();
	for(uint32_t cityIdx = 1; cityIdx < graph.size(); ++cityIdx){
		std::vector<uint32_t> subset(graph.size());
		std::iota( std::begin(subset), std::end(subset),0);
		//auto smallerSubset = subsetWithout(subset,cityIdx);	
		auto& m = arr[cityIdx];
		auto cost = m[subset];

		if(min > cost + graph[cityIdx][0])
			min = cost +  graph[cityIdx][0];
	}
	return min;
}

} // end namespace mirazabal

int main()
{
	auto graph = mirazabal::createGraphFromFile("tsp.txt");
	for(auto& vec: graph){
		for(auto val : vec){
			std::cout << "    " << val;
		}
		 std::cout << std::endl;
	}
	
	std::cout << mirazabal::tsp_dynamic(graph) << std::endl; 
	return 0;
}

