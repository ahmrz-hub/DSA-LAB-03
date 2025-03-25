#include <iostream>
#include <vector>
using namespace std;

template <typename type>
class list {
protected:
	vector<type> arr;
	int maxsize;
	int currentSize;

public:
	virtual type sum_ofPrime() = 0;
	virtual type secondMaxEven() = 0;
	virtual type secondMinOdd() = 0;
	virtual void printDuplicates() = 0;
	virtual void rotateClockwaise(int r) = 0;
	virtual void rotateanitclockwaise(int rt) = 0;
};

template <typename type>
class CustomList : public list<type> {
public:
	// Constructor with default value
	CustomList(type* arr1 = nullptr, int max = 5, int cs = 0) {
		this->maxsize = max;
		this->currentSize = cs;
		if (arr1 != nullptr) {
			for (int i = 0; i < this->maxsize; i++) {
				this->arr.push_back(arr1[i]);
			}
		}
	}

	// Copy Constructor
	CustomList(const CustomList& other) {
		this->arr = other.arr;
		this->maxsize = other.maxsize;
		this->currentSize = other.currentSize;
	}

	type sum_ofPrime() override {
		type sum = 0;
		for (auto i : this->arr) {
			if (isPrime(i)) {
				sum += i;
			}
		}
		return sum;
	}

	type secondMaxEven() override {
		vector<type> evens;
		for (auto i : this->arr) {
			if (i % 2 == 0) {
				evens.push_back(i);
			}
		}
		if (evens.size() < 2) {
			cout << "Not enough even numbers." << endl;
			return type();
		}
		// Simple bubble sort to sort evens in descending order
		for (int i = 0; i < evens.size() - 1; i++) {
			for (int j = 0; j < evens.size() - i - 1; j++) {
				if (evens[j] < evens[j + 1]) {
					swap(evens[j], evens[j + 1]);
				}
			}
		}
		return evens[1];
	}

	type secondMinOdd() override {
		vector<type> odds;
		for (auto i : this->arr) {
			if (i % 2 != 0) {
				odds.push_back(i);
			}
		}
		if (odds.size() < 2) {
			cout << "Not enough odd numbers." << endl;
			return type();
		}
		// Simple bubble sort to sort odds in ascending order
		for (int i = 0; i < odds.size() - 1; i++) {
			for (int j = 0; j < odds.size() - i - 1; j++) {
				if (odds[j] > odds[j + 1]) {
					swap(odds[j], odds[j + 1]);
				}
			}
		}
		return odds[1];
	}

	void printDuplicates() override {
		vector<type> duplicates;
		for (int i = 0; i < this->arr.size(); i++) {
			for (int j = i + 1; j < this->arr.size(); j++) {
				if (this->arr[i] == this->arr[j] && find(duplicates.begin(), duplicates.end(), this->arr[i]) == duplicates.end()) {
					duplicates.push_back(this->arr[i]);
				}
			}
		}
		for (auto dup : duplicates) {
			cout << dup << " ";
		}
		cout << endl;
	}

	void rotateClockwaise(int r) override {
		int n = this->arr.size();
		if (n == 0) return;
		r = r % n;
		reverse(this->arr.begin(), this->arr.end());
		reverse(this->arr.begin(), this->arr.begin() + r);
		reverse(this->arr.begin() + r, this->arr.end());
	}

	void rotateanitclockwaise(int rt) override {
		int n = this->arr.size();
		if (n == 0) return;
		rt = rt % n;
		reverse(this->arr.begin(), this->arr.end());
		reverse(this->arr.begin(), this->arr.begin() + (n - rt));
		reverse(this->arr.begin() + (n - rt), this->arr.end());
	}

	// Destructor
	~CustomList() {
		// No need to delete arr as it is a vector
	}

	void display() {
		for (auto i : this->arr) {
			cout << i << " ";
		}
		cout << endl;
	}

private:
	bool isPrime(type num) {
		if (num <= 1) return false;
		for (type i = 2; i * i <= num; i++) {
			if (num % i == 0) return false;
		}
		return true;
	}

	void reverse(typename vector<type>::iterator start, typename vector<type>::iterator end) {
		while (start < end) {
			swap(*start, *end);
			start++;
			end--;
		}
	}
};

int main() {
	int arr[] = { 1, 20, 30, 40, 40 };
	CustomList<int> l1(arr);
	int choice, rotations;

	while (true) {
		cout << "Menu:" << endl;
		cout << "1. Display list" << endl;
		cout << "2. Sum of prime numbers" << endl;
		cout << "3. Second maximum even number" << endl;
		cout << "4. Second minimum odd number" << endl;
		cout << "5. Print duplicates" << endl;
		cout << "6. Rotate list clockwise" << endl;
		cout << "7. Rotate list anti-clockwise" << endl;
		cout << "8. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			l1.display();
			break;
		case 2:
			cout << "Sum of prime numbers: " << l1.sum_ofPrime() << endl;
			break;
		case 3:
			cout << "Second maximum even number: " << l1.secondMaxEven() << endl;
			break;
		case 4:
			cout << "Second minimum odd number: " << l1.secondMinOdd() << endl;
			break;
		case 5:
			cout << "Duplicate elements: ";
			l1.printDuplicates();
			break;
		case 6:
			cout << "Enter number of rotations: ";
			cin >> rotations;
			l1.rotateClockwaise(rotations);
			break;
		case 7:
			cout << "Enter number of rotations: ";
			cin >> rotations;
			l1.rotateanitclockwaise(rotations);
			break;
		case 8:
			return 0;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	return 0;
}
