#include <vector>
#include <list>
#include <map>
#include <string>

#include "Graph.h"

typedef std::map<char, std::list<int> > cmap;
typedef std::pair<char, std::list<int> > cpair;

class LCSS
{
public:
	LCSS (): x(""), y("") {};

	LCSS (std::string const & a, std::string const & b)
	{
		if (a.size() > b.size())
		{
			x = a;
			y = b;
		}
		else
		{
			x = b;
			y = a;
		}
	}

	int LongestSubsequence()
	{
		// clear index table
		index_tbl.clear();

		// build index tree
		for (unsigned int i=0; i<x.size(); i++)
		{
			cmap::iterator charlist = index_tbl.find(x[i]);
			if (charlist == index_tbl.end())
			{
				std::list<int> temp;
				temp.push_back(i);
				index_tbl.insert( cpair(x[i], temp) );
			}
			else
			{
				charlist->second.push_back(i);
			}
		}

		// build vector of indices from the second string
		std::vector<int> y_vec;
		for (unsigned int i=0; i<y.size(); i++)
		{
			cmap::iterator charlist = index_tbl.find(y[i]);
			if (charlist != index_tbl.end())
			{
				while(!y_vec.empty() && !charlist->second.empty() && charlist->second.front() < y_vec[y_vec.size()-1])
				{
					charlist->second.pop_front();
				}
				if (!charlist->second.empty())
				{
					y_vec.push_back(charlist->second.front());
					charlist->second.pop_front();
				}
			}
		}

		return y_vec.size();

		// build reverse graph, G
		Graph dag;

		// graph class calculation
		return dag.LongestSubsequence(y_vec);
	}

private:
	std::string x;
	std::string y;
	cmap index_tbl;
};