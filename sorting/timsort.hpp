#ifndef TIMSORT_HPP
#define TIMSORT_HPP 1

#include <algorithm>
#include <stack>
#include "insertionSort.hpp"

namespace Timsort {

	const int MIN_GALLOP = 7;

	template <class RandomIt>
	RandomIt ReverseIt(std::reverse_iterator<RandomIt> it) {
		return it.base();
	}

	template <class RandomIt>
	std::reverse_iterator<RandomIt> ReverseIt(RandomIt it) {
		return std::reverse_iterator<RandomIt>(it);
	}

	template<class Compare>
	struct ReversedCompare {
		Compare compare;
		template<class Left, class Right>
		bool operator()(const Left& left, const Right& right) {
			return compare(right,left);
		}
	};

	template <class Compare>
	Compare ReverseComp(ReversedCompare<Compare> compare) {
		return compare.compare;
	}

	template <class Compare>
	ReversedCompare<Compare> ReverseComp(Compare compare) {
		return ReversedCompare<Compare>{compare};
	}

	template<class SourceRandomIt, class TargetRandomIt, class Compare>
	TargetRandomIt Gallop(SourceRandomIt sourceIt, TargetRandomIt targetBegin, TargetRandomIt targetEnd, Compare Comp) {
		//Gallop through the list checking if sourceIt
		//	fits between 2^(i-1) and 2^i
		//	then do a binary search within that range
		auto length = std::distance(targetBegin, targetEnd);
		auto sourceValue = *sourceIt;
		if (!Comp(*targetBegin, sourceValue)) {
			return targetBegin;
		} else if (Comp(*(std::prev(targetEnd)), sourceValue)) {
			return targetEnd;
		}
		for (int i=1;;++i) {
			auto leftBoundPos = (1<<(i-1))-1;
			auto rightBoundPos = (1<<i)-1;
			if (rightBoundPos >= length) {
				rightBoundPos = length-1;
			}
			auto leftBound = targetBegin + leftBoundPos;
			auto rightBound = targetBegin + rightBoundPos;
			if (Comp(*leftBound, sourceValue) && !Comp(*rightBound, sourceValue)) {
				auto resultingPos = std::lower_bound(leftBound, std::next(rightBound), sourceValue, Comp);
				return resultingPos;
			}
		}
	}

	template<class LeftRandomIt, class RightRandomIt, class InsertRandomIt, class Compare>
	void MergeInto(LeftRandomIt leftIt, LeftRandomIt leftEnd, RightRandomIt rightIt, RightRandomIt rightEnd, InsertRandomIt insertIt, Compare Comp) {
		//Begin merging
		while (1) {
			int leftRunCount = 0;
			int rightRunCount = 0;
			bool hitBounds = false;
			while (leftRunCount < MIN_GALLOP && rightRunCount < MIN_GALLOP) {
				//While there are elements in both lists
				auto leftValue = *leftIt;
				auto rightValue = *rightIt;

				if (!Comp(rightValue, leftValue)) {
					//Left list's first element is inserted
					*insertIt = leftValue;
					++leftIt;
					++leftRunCount;
					rightRunCount = 0;
				} else {
					//Right list's first element is inserted
					*insertIt = rightValue;
					++rightIt;
					++rightRunCount;
					leftRunCount = 0;
				}
				++insertIt;
				if (leftIt == leftEnd || rightIt == rightEnd) {
					//At least one list is empty
					hitBounds = true;
					break;
				}
			}
			//Either going to enter galloping mode or hit our bounds
			if (hitBounds) {
				//At least one list is empty
				break;
			}
			//Standard merge hit a long run, try galloping
			do {
				//Gallop to the right first to find a position for leftIt
				auto rightInsertIt = Gallop(leftIt, rightIt, rightEnd, Comp);
				auto rightRunCount = std::distance(rightIt, rightInsertIt);
				std::move(rightIt, rightInsertIt, insertIt);
				std::advance(insertIt, rightRunCount);
				std::advance(rightIt, rightRunCount);
				*insertIt = *leftIt;
				++leftIt;
				++insertIt;

				if (leftIt == leftEnd || rightIt == rightEnd) {
					//At least one list is empty
					hitBounds = true;
					break;
				}

				//Gallop to the left now to find a position for rightIt
				//	Pass an altered Comp function to preserve stability
				auto AlteredComp = [&Comp](const auto &left, const auto &right) -> bool {
					return !Comp(right,left);
				};
				auto leftInsertIt = Gallop(rightIt, leftIt, leftEnd, AlteredComp);
				auto leftRunCount = std::distance(leftIt, leftInsertIt);
				std::move(leftIt, leftInsertIt, insertIt);
				std::advance(insertIt, leftRunCount);
				std::advance(leftIt, leftRunCount);
				*insertIt = *rightIt;
				++rightIt;
				++insertIt;

				if (leftIt == leftEnd || rightIt == rightEnd) {
					//At least one list is empty
					hitBounds = true;
					break;
				}
				//Repeat if at least one run was long enough
			}	while (leftRunCount < MIN_GALLOP && rightRunCount < MIN_GALLOP);
			if (hitBounds) {
				//At least one list is empty
				break;
			}
			//Going back to standard merge
		}
		//Now at least one list is empty
		if (leftIt != leftEnd) {
			//Insert all of the left list into the list (right is empty)
			std::move(leftIt, leftEnd, insertIt);
		} else if (rightIt != rightEnd) {
			//Insert all of the right list into the list (left is empty)
			std::move(rightIt, rightEnd, insertIt);
		}
	}

	template<class RandomIt, class Compare>
	void Merge(RandomIt begin, RandomIt middle, RandomIt end, Compare Comp) {
		size_t leftLength = std::distance(begin, middle);
		size_t rightLength = std::distance(middle, end);

		if (leftLength > rightLength) {
			//Left list is bigger, swap everything around and recursively call this function
			Merge(ReverseIt(end), ReverseIt(middle), ReverseIt(begin), ReverseComp(Comp));
			return;
		}
		//Now guaranteed that [begin,middle) <= [middle,end)

		//Determine if there are any leftmost positions that are already in place
		auto newLeftBegin = std::upper_bound(begin, middle, *middle, Comp);
		if (newLeftBegin == middle) {
			//Everything in the left list is smaller than the first in the right list, we're done
			return;
		}
		//Determine if there are any righmost positions that are already in place
		auto rightEnd = std::upper_bound(middle, end, *(std::prev(middle)), Comp);
		if (rightEnd == middle) {
			//Everything in the left list is smaller than the first in the right list, we're done
			return;
		}
		//	"These preliminary searches[newLeftBegin&rightEnd] may not pay off, and can be expected *not* to
		//	repay their cost if the data is random.  But they can win huge in all of
		//	time, copying, and memory savings when they do pay"
		//	According to https://svn.python.org/projects/python/trunk/Objects/listsort.txt

		// newLeftBegin saved std::distance(begin, newLeftBegin)*sizeof(RandomIt) bytes of extra space usage
		// rightEnd saved std::distance(rightEnd, end)*sizeof(RandomIt) bytes of extra space usage
		//Save the left list in a temp because we'll be overwriting it as we insert
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;
		std::vector<ValueType> tempList(newLeftBegin, middle);
		auto leftIt = tempList.begin();
		auto leftEnd = tempList.end();

		auto rightIt = middle;

		auto insertIt = newLeftBegin;

		MergeInto(leftIt, leftEnd, rightIt, rightEnd, insertIt, Comp);
	}

	template<class RandomIt>
	struct Run {
		RandomIt begin;
		size_t length;
		Run(RandomIt b, size_t l) : begin(b), length(l) {};
	};

	size_t CalculateMinrun(size_t length) {
		//Take the six most significant bits of the size of the array,
		//	adds one if any of the remaining bits are set, and uses
		//	that result as the minrun. This algorithm works for all arrays,
		//	including those smaller than 64.
		size_t mostSignificant6 = length;
		size_t extraBit = 0;
		while (mostSignificant6 >= (1<<6)) {
			//While there are more than 6 significan bits
			//[Or] the least significan bit with 1
			extraBit |= mostSignificant6 & 1;
			//[Right shift] the main number
			mostSignificant6 >>= 1;
		}
		return mostSignificant6 + extraBit;
	}

	template<class RandomIt, class Compare>
	size_t FindExistingRunLength(RandomIt begin, RandomIt end, Compare Comp) {
		size_t length = std::distance(begin,end);
		if (length < 2) {
			return length;
		}
		auto runIt = begin;
		if (!Comp(*(runIt+1), *(runIt))) {
			//Increasing run
			runIt += 2;
			while (runIt != end && !Comp(*(runIt), *(runIt-1))) {
				//Grow the run as long as the elements are increasing
				++runIt;
			}
		} else {
			//Strictly decreasing run
			runIt += 2;
			while (runIt != end && Comp(*(runIt), *(runIt-1))) {
				//Grow the run as long as the elements are strictly decreasing
				++runIt;
			}
			//Since they were strictly decreasing, we can easily
			//	reverse them to get a stable increasing run
			std::reverse(begin, runIt);
		}
		return std::distance(begin,runIt);
	}

	template<class RandomIt, class Compare>
	void MaintainStackInvariants(std::stack<Run<RandomIt>> *runStack, Compare Comp) {
		while (runStack->size() >= 3) {
			//Pop the top three off the stack
			Run<RandomIt> a = runStack->top();
			runStack->pop();
			Run<RandomIt> b = runStack->top();
			runStack->pop();
			Run<RandomIt> c = runStack->top();
			runStack->pop();

			if ((a.length<=(b.length+c.length)) || (b.length<=c.length)) {
				//Invariant fails
				if (a.length < c.length) {
					//Merge a and b
					size_t totalLength = a.length+b.length;
					Merge(b.begin, b.begin+b.length, b.begin+totalLength, Comp);
					runStack->push(c);
					runStack->emplace(b.begin, totalLength);
				} else {
					//Merge b and c
					//	ties favor c
					size_t totalLength = b.length+c.length;
					Merge(c.begin, c.begin+c.length, c.begin+totalLength, Comp);
					runStack->emplace(c.begin, totalLength);
					runStack->push(a);
				}
			}
		}
	}

	template<class RandomIt, class Compare>
	void MergeRemainingOnStack(std::stack<Run<RandomIt>> *runStack, Compare Comp) {
		while (runStack->size() >= 2) {
			//Pop top 2 off stack
			Run<RandomIt> a = runStack->top();
			runStack->pop();
			Run<RandomIt> b = runStack->top();
			runStack->pop();

			//Merge them then push the result
			size_t totalLength = a.length+b.length;
			Merge(b.begin, b.begin+b.length, b.begin+totalLength, Comp);
			runStack->emplace(b.begin, totalLength);
		}
	}

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		size_t length = std::distance(begin,end);
		const size_t minRunLength = CalculateMinrun(length);

		std::stack<Run<RandomIt>> runStack;

		size_t runStart = 0;

		while (runStart < length) {
			//More array remaining
			size_t runLength = FindExistingRunLength(begin+runStart, end, Comp);
			if (runLength < minRunLength) {
				//Run isnt long enough
				if ((runStart+minRunLength) < length) {
					//There are at least minRunLength elements remaining
					runLength = minRunLength;
				} else {
					//There are less than minRunLength elements remaining
					runLength = length-runStart;
				}
				//Use insertion sort becase the run wasnt long enough
				InsertionSort::Sort(begin+runStart, begin+runStart+runLength, Comp);
			}
			//Push the current run onto the stack
			runStack.emplace(begin+runStart, runLength);
			//Ensure the stack invariants are maintained
			MaintainStackInvariants(&runStack, Comp);
			//Increase the start to after this run
			runStart += runLength;
		}

		MergeRemainingOnStack(&runStack, Comp);
	}
} //namespace Timsort

#endif //TIMSORT_HPP