#include <Windows.h>
#include <iostream>

struct Process {
	int processId;
	int burstTime;
	int arrivalTime;
	
};

struct list {
	Process process;
	struct list* next;
	struct list* before;
}*head;

typedef struct list JOBQUE;
typedef struct Process Process;


void insertion(Process p)
{

	if (head != NULL){

		JOBQUE* tmp = (JOBQUE*)malloc(sizeof(JOBQUE));

		tmp->process = p;


		if (tmp->process.arrivalTime < head->process.arrivalTime) {
			tmp->next = head;
			tmp->before = NULL;
			head->before = tmp;
			head = tmp;
		}
		else {
			JOBQUE* tmp2 = head;

			while (tmp->process.arrivalTime > tmp2->process.arrivalTime) {

				tmp2 = tmp2->next;
			}
			if (tmp->process.arrivalTime < tmp2->process.arrivalTime) {
				if (tmp2->before != NULL)
					tmp2->before->next = tmp;
				tmp->before = tmp2->before;
				tmp2->before = tmp;
				tmp->next = tmp2;
			}
			else {
				if (tmp->process.burstTime < tmp2->process.burstTime) {
					if (tmp2->before != NULL) {
						tmp2->before->next = tmp;
					}
					tmp->before = tmp2->before;
					tmp2->before = tmp;
					tmp->next = tmp2;
				}
				else {
					if (tmp2->before != NULL) {
						tmp2->before->next = tmp;
					}
					tmp->next = tmp2->next;
					tmp2->next = tmp;
					tmp->before = tmp2;
				}
			}
		}	
	}
	else {
		head = (JOBQUE*)malloc(sizeof(JOBQUE));;

		head->process = p;
		head->next = NULL;
		head->before = NULL;
	}
}

void print() {

	if (head != NULL) {
		JOBQUE* tmp = head;

		std::cout << "Process que is ..:";

		while (tmp != NULL) {

			std::cout << tmp->process.processId << " ";
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
}

void setArriveTime(int ms) {


	JOBQUE* tmp = head;

	while (tmp != NULL) {

		
		tmp->process.arrivalTime -= ms;
		tmp = tmp->next;
	}


}

void executeProcess() {

	if (head != NULL) {
		std::cout << "Executing process : " << head->process.processId << std::endl;
		std::cout << ".";
		for (int i = 0; i < 10;i++) {
			Sleep((head->process.burstTime)/10);
			std::cout << ".";
		}
		
		std::cout << "\nExecuted process : " << head->process.processId << std::endl;

		
		if (head->next == NULL) {
			free(head);
			head = NULL;
		}
		else {
			JOBQUE* tmp = head;
			tmp->next->before = NULL;

			head = tmp->next;

			setArriveTime(tmp->process.burstTime);

			free(tmp);

		}
		
	}
}


int main() {


	const int size = 10;
	Process processArray[] = {
		{ 1,6,2 },
		{ 2,2,5},
		{ 3,8,1 },
		{ 4,3,0},
		{ 5,4,4}
	};

	std::cout << "Not sorted que is ..:";

	for (int i = 0; i < sizeof(processArray) / sizeof(Process); i++) {

		std::cout << processArray[i].processId << " " ;

	}

	std::cout << std::endl;
	//4 3 5 2 1

	for (int i = 0; i < sizeof(processArray)/sizeof(Process); i++) {

		insertion(processArray[i]);

	}

	std::cout << "Sorted que is ..:\n		";
	print();
	for (int i = 0; i < sizeof(processArray) / sizeof(Process);i++) {
		
		executeProcess();

		print();
		
	}

	

	return 0;


}
