#ifndef PATIENCESORT_HPP
#define PATIENCESORT_HPP 1

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "mergeSort.hpp"

namespace PatienceSort {

	template<class RandomIt, class Compare>
	void MergePiles(std::vector<std::pair<RandomIt,RandomIt>> iteratorPairList, Compare Comp) {
		size_t length;
		while ((length = iteratorPairList.size()) > 1) {
			for (size_t i=1; i<length; i+=2) {
				MergeSort::Merge(iteratorPairList.at(i-1).first, iteratorPairList.at(i).first, iteratorPairList.at(i).second, Comp);
				iteratorPairList.at(i/2).first = iteratorPairList.at(i-1).first;
				iteratorPairList.at(i/2).second = iteratorPairList.at(i).second;
			}
			if (length % 2 == 1) {
				//List length is odd, last one isnt going to get merged,
				//	add it to the temp list
				iteratorPairList.at(length/2) = iteratorPairList.back();
			}
			iteratorPairList.erase(iteratorPairList.begin()+((length+1)/2), iteratorPairList.end());
		}
	}

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;
		std::vector<std::vector<ValueType>> piles;

		auto it = begin;
		while (it != end) {
			auto itValue = *it;
			//Do a binary search to see which pile this item goes in
			auto pileIt = std::upper_bound(piles.begin(), piles.end(), itValue, [&Comp](const ValueType &value, const std::vector<ValueType> &pile) {
				return Comp(value, pile.back());
			});
			if (pileIt == piles.end()) {
				//List not found, make a new one with just this value
				piles.emplace_back(std::vector<ValueType>{itValue});
			} else {
				//List found, add this value to it
				pileIt->emplace_back(itValue);
			}
			++it;
		}
		//Now we have 'piles.size()' reverse-sorted lists
		//Move them all back into the orignal list so they can be merged
		std::vector<std::pair<RandomIt,RandomIt>> sortedListIteratorPairList;
		it = begin;
		for (auto &pile : piles) {
			auto pileSize = pile.size();
			//Move using reverse iterators so the pile is back in order
			std::move(pile.rbegin(), pile.rend(), it);
			//Store the iterator pair to be used when merging
			sortedListIteratorPairList.emplace_back(it, std::next(it, pileSize));
			std::advance(it, pileSize);
		}
		//Merge piles
		MergePiles(sortedListIteratorPairList, Comp);
	}
} //namespace PatienceSort

#endif //PATIENCESORT_HPP