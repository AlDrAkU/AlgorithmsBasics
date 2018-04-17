#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <array>
#include <set>
#include <map>
#include <string>
#include <functional>

int main()
{
	//a.Define a source container
	std::cout << "a.Define a source container" << std::endl;
	std::vector<int> intVector(20);
	std::generate(intVector.begin(), intVector.end(), [] {return (rand() % 20 + 1); });

	//b. Copy all elements to the console
	std::cout << "b. Copy all elements to the console" << std::endl;
	std::ostream_iterator<int> oStream(std::cout, " ");
	std::copy(intVector.begin(), intVector.end(),oStream);
	std::cout << std::endl;

	//c. Copy the odd elements to the console
	std::cout << "c. Copy the odd elements to the console" << std::endl;
	std::copy_if(intVector.begin(), intVector.end(), oStream, [](int i) {
		if (i % 2 != 0)
		{
			return true;
		}
		return false;
	});
	std::cout << std::endl;

	//d. Copy a number of elements to the console stream
	std::cout << "d. Copy a number of elements to the console stream" << std::endl;
	std::copy_n(intVector.begin() + 10, int(intVector.size() / 4), oStream);
	std::cout << std::endl;

	//e. Copy the odd source elements to a std::deque
	std::cout << "e.Copy the odd source elements to a std::deque" << std::endl;
	std::deque<int> intDeque{};
	std::copy_if(intVector.begin(), intVector.end(), std::back_inserter(intDeque), [](int i) {
		if (i % 2 != 0)
		{
			return true;
		}
		else false;
	});
	for (int i : intDeque)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	std::deque<int> intDeque2{};
	std::copy_if(intVector.begin(), intVector.end(), std::front_inserter(intDeque2), [](int i) {
		if (i % 2 != 0)
		{
			return true;
		}
		else false;
	});
	for (int i : intDeque2)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;

	//f. Copy the odd elements to an std::set
	std::cout << "f. Copy the odd elements to an std::set" << std::endl;
	std::set<int> intSet{};
	std::copy_if(intVector.begin(), intVector.end(), std::inserter(intSet, intSet.begin()), [](int i) {
		if (i % 2 != 0)
		{
			return true;
		}
		return false;
	});
	for (int i : intSet)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;


	//g. Copy some elements to and std::array
	std::cout << "g. Copy some elements to and std::array" << std::endl;
	std::array<int, 10> intArr{};
	std::copy_n(intVector.begin(), 5, std::copy_backward(intArr.begin() + 5, intArr.end(), intArr.end()));
	for (int i : intArr)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//3.2.2. Replace and unique algorithm
	std::cout << "3.2.2. Replace and unique algorithm" << std::endl;
	std::vector<int> randVector(20);
	std::generate(randVector.begin(), randVector.end(), []() {return rand() % 13 + 3; });
	std::for_each(randVector.begin(), randVector.end(), [](int i) {std::cout << i << ' '; });
	std::cout << std::endl;
	std::replace_if(randVector.begin(), randVector.end(), [](int i) {if (i % 3 == 0)return true; return false; }, 0);
	std::for_each(randVector.begin(), randVector.end(), [](int i) {std::cout << i << ' '; });
	std::cout << std::endl;
	std::vector<int>::iterator it = std::unique(randVector.begin(), randVector.end());
	randVector.erase(it, randVector.end());
	std::for_each(randVector.begin(), randVector.end(), [](int i) {std::cout << i << ' '; });
	std::cout << std::endl;
	std::vector<int>::iterator it2 = std::unique(randVector.begin(), randVector.end(), [](int i, int j) {return (!(i % 2) && !(j % 2)); });
	randVector.erase(it2, randVector.end());
	std::for_each(randVector.begin(), randVector.end(), [](int i) {std::cout << i << ' '; });
	std::cout << std::endl;
	std::cout << std::endl;


	//3.2.3. Transform algorithm
	std::cout << "3.2.3. Transform algorithm" << std::endl;
	//a.Get all the keys of a map.
	std::cout << "a.Get all the keys of a map." << std::endl;
	std::map<std::string, int> aMap{};
	aMap["Marleen"] = 5;
	aMap["Bart"] = 3;
	aMap["Steven"] = 1;
	std::vector<std::string> keys{};
	keys.resize(aMap.size());
	std::transform(aMap.begin(), aMap.end(), keys.begin(), [](std::pair<std::string, int> pair) {return pair.first; });
	std::ostream_iterator<std::string> stringStream{std::cout, ", "};
	std::copy(keys.begin(), keys.end(), stringStream);
	std::cout << std::endl;

	//b. Subtract the corresponding elements of 2 containers.
	std::cout << "b. Subtract the corresponding elements of 2 containers." << std::endl;
	std::vector<int> rVec1(10);
	std::vector<int> rVec2(10);
	std::generate(rVec1.begin(), rVec1.end(), []() {return rand() % 10; });
	std::generate(rVec2.begin(), rVec2.end(), []() {return rand() % 10; });
	std::copy(rVec1.begin(), rVec1.end(), oStream);
	std::cout << std::endl;
	std::copy(rVec2.begin(), rVec2.end(), oStream);
	std::cout << std::endl;
	std::vector<int> sRVec{};
	sRVec.resize(rVec1.size());
	std::transform(rVec1.begin(), rVec1.end(), rVec2.begin(), sRVec.begin(), [](int i, int j) {return i + j; });
	std::copy(sRVec.begin(), sRVec.end(), oStream);
	std::cout << std::endl;
	std::cout << std::endl;

	//3.2.4. Set operations (on sorted ranges)
	std::cout << "3.2.4. Set operations (on sorted ranges)" << std::endl;
	std::vector<int> v1{1,3,5,5,6,7,8,9};
	std::vector<int> v2{1,2,3,4};
	std::vector<int> v3{6,9};
	std::vector<int> v4{1,3,5,5,6,7,8,9,1,2,3,4};
	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), oStream);
	std::cout << std::endl;
	std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), oStream);
	std::cout << std::endl;
	std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), oStream);
	std::cout << std::endl;
	std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
	std::cout << std::boolalpha << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << std::endl;
	std::inplace_merge(v4.begin(), v4.begin() + 8, v4.end());
	std::copy(v4.begin(), v4.end(), oStream);
	std::cout << std::endl;
	std::cout << std::endl;


	//3.2.5. Heap operations
	std::cout << "3.2.5. Heap operations" << std::endl;
	//a. Heap data structures
	std::cout << "a. Heap data structures" << std::endl;
	//b. Turn a vector into a max heap
	std::cout << "b. Turn a vector into a max heap" << std::endl;
	std::vector<int> rV{ 5,8,7,3,1,4,9,5,7 };
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::is_heap(rV.begin(), rV.end()) << std::endl;
	for (std::vector<int>::const_iterator it{ rV.cbegin() }; it != std::is_heap_until(rV.cbegin(), rV.cend()); ++it) std::cout << *it << ' ';
	std::cout << std::endl;
	std::make_heap(rV.begin(), rV.end());
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::is_heap(rV.begin(), rV.end()) << std::endl;
	std::cout << std::endl;

	//c. Get the first element of the heap keeping the heap property
	std::cout << "c. Get the first element of the heap keeping the heap property" << std::endl;
	std::pop_heap(rV.begin(), rV.end());
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::is_heap(rV.begin(), rV.end()) << std::endl;
	for (std::vector<int>::const_iterator it{ rV.cbegin() }; it != std::is_heap_until(rV.cbegin(), rV.cend()); ++it) std::cout << *it << ' ';
	std::cout << std::endl;
	std::cout << *std::is_heap_until(rV.cbegin(), rV.cend()) << std::endl;
	rV.erase(std::is_heap_until(rV.cbegin(), rV.cend()));
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::is_heap(rV.begin(), rV.end()) << std::endl;
	std::cout << std::endl;

	//d. Add an element keeping the heap property
	std::cout << "d. Add an element keeping the heap property" << std::endl;
	rV.push_back(25);
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::is_heap(rV.begin(), rV.end()) << std::endl;
	for (std::vector<int>::const_iterator it{ rV.cbegin() }; it != std::is_heap_until(rV.cbegin(), rV.cend()); ++it) std::cout << *it << ' ';
	std::cout << std::endl;
	std::push_heap(rV.begin(), rV.end());
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::boolalpha << std::is_heap(rV.begin(), rV.end()) << std::endl;
	std::cout << std::endl;


	//e. Operation sort_heap
	std::cout << "e. Operation sort_heap" << std::endl;
	std::sort_heap(rV.begin(), rV.end());
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::endl;

	//f. A min heap
	std::cout << "f. A min heap" << std::endl;
	std::sort_heap(rV.begin(), rV.end(), std::greater<int>());
	std::copy(rV.begin(), rV.end(), oStream);
	std::cout << std::endl;
	std::cout << std::endl;

	//3.2.6. Permutations
	std::cout << "3.2.6. Permutations" << std::endl;
	std::vector<int> perm{ 3,1,4 };
	std::sort(perm.begin(), perm.end());
	do
	{
		std::copy(perm.begin(), perm.end(), oStream);
		std::cout << std::endl;
	} while (std::next_permutation(perm.begin(), perm.end()));
	std::cout << std::endl;
	std::sort(perm.begin(), perm.end(), std::greater<int>());
	do
	{
		std::copy(perm.begin(), perm.end(), oStream);
		std::cout << std::endl;
	} while (std::prev_permutation(perm.begin(), perm.end()));



	std::cin.get();
}