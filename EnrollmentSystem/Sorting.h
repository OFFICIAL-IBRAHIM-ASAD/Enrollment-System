// Sorting.h
#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "Student.h" // Needs to know about Student structure

// Sorts by studentName by default, then studentId for ties
// If sortByKSUID is true, sorts by studentId first.
inline void selectionSortStudents(std::vector<Student>& students, bool sortByName = true) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            bool comparisonResult;
            if (sortByName) { // Default: sort by name
                comparisonResult = (students[j].studentName < students[min_idx].studentName) ||
                                   (students[j].studentName == students[min_idx].studentName && students[j].studentId < students[min_idx].studentId);
            } else { // Sort by ID
                comparisonResult = students[j].studentId < students[min_idx].studentId;
            }
            if (comparisonResult) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(students[i], students[min_idx]);
        }
    }
}

#endif //SORTING_H