#pragma once

#include <vector>
#include <string>

class MergeSort {
public:
	static void sort(std::vector<std::pair<std::string, int>>& si);
private:
	static void merge_sort(std::vector<std::pair<std::string, int>>& si, int l, int r);
	static void merge(std::vector<std::pair<std::string, int>>& si, int l, int m, int r);
};