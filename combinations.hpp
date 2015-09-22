#ifndef COMBINATIONS_HPP_INCLUDED
#define COMBINATIONS_HPP_INCLUDED
#include <iterator>
#include <vector>
#include <algorithm>
#include <cassert>

//! Combination generator
template<class ValueType>
class Combinations
{
	typedef size_t IndexType; // integral
	typedef std::vector<IndexType> IndexVector;
	typedef std::vector<ValueType> CombinationVector;
public:
	//! Constructs with values { 0, ..., n - 1 } by std::iota().
	Combinations(size_t n, size_t k) : 
		initial_(Sequence<size_t>(k)), 
		values_(Sequence<size_t>(n)) 
	{ assert(n > 0); assert(k < n); };

	//! Constructs with a given vector \a V.
	Combinations(CombinationVector const& V, size_t k) : 
		initial_(Sequence<size_t>(k)), 
		values_(V) 
	{ assert(V.size() > 0); assert(k < V.size()); };

	class iterator : public std::iterator<std::input_iterator_tag, CombinationVector>
	{
		public:
			iterator(Combinations const& C) : C_(C), seq_(C.initial_) { }
			iterator(Combinations const& C, IndexVector const& seq) : C_(C), seq_(seq) { }
			iterator(iterator const& it) : C_(it.C_), seq_(it.seq_)  { }

			iterator& operator++()
			{
				if(seq_[0] == C_.values_.size() - seq_.size())
					seq_.clear();
				else
					next();

				return *this;
			}

			iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }

			bool operator==(iterator const& rhs) const { return seq_ == rhs.seq_; }
			bool operator!=(iterator const& rhs) const { return seq_ != rhs.seq_; }

			CombinationVector operator*() const 
			{
				CombinationVector V;
				for(size_t const i : seq_)  V.push_back(C_.values_[i]);
				return V;
			}

		private:
			iterator() { }; // forbidden

			Combinations const& C_;
			IndexVector seq_;

			// Assumes that seq_ is a strictly monotonic sequence.
			void next()
			{
				auto const n = C_.values_.size();
				assert(seq_[0] < (n - seq_.size()));
				size_t const k = seq_.size();
				// Visits and counts up from the end of the array
				// until no carry occurs.
				for(size_t i = 0; i < k; ++i)
				{
					// A position to examine
					size_t const idx = (k - 1) - i;

					size_t const vv = seq_[idx];
					assert(vv < n);

					// If the value is not maximum,
					// incriments it and fills followings with the consecutive values.
					if(vv != (n - 1) - i)
					{
						for(size_t j = 0; idx+j < k; ++j) seq_[idx+j] = (vv+1) + j;

						break;
					}
				}
			}
	};

	iterator begin() const { return iterator(*this); }
	iterator end() const { return iterator(*this, IndexVector()); }

	CombinationVector const& Values() const { return values_; }

	private:
		IndexVector const initial_;
		CombinationVector const values_;

		template<class T>
		static std::vector<T> Sequence(size_t const n)
		{
			std::vector<T> I(n);
			std::iota(I.begin(), I.end(), T());
			return I;
		}
};

#endif // COMBINATIONS_HPP_INCLUDED
