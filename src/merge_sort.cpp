#include "../include/merge_sort.h"

#include <vector>
#include <string>




void MergeSort::sort(std::vector<std::pair<std::string, int>>& si) {
	merge_sort(si, 0, (int)si.size() - 1);
}

void MergeSort::merge_sort(std::vector<std::pair<std::string, int>>& si, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		merge_sort(si, l, m);
		merge_sort(si, m + 1, r);
		merge(si, l, m, r);
	}
}

void MergeSort::merge(std::vector<std::pair<std::string, int>>& si, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	std::vector<std::pair<std::string, int>> L(n1), R(n2);

	for (int i = 0; i < n1; i++) {
		L[i] = si[l + i];
	}
	for (int i = 0; i < n2; i++) {
		R[i] = si[m + 1 + i];
	}

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i].second >= R[j].second) {
			si[k] = L[i];
			i++;
		}
		else {
			si[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		si[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		si[k] = R[j];
		j++;
		k++;
	}
}