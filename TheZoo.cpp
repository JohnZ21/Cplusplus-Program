#include <iostream>
#include <iomanip>
#include <jni.h>
#include <vector>
#include <fstream>

#include "Animal.h"
#include "Bat.h"
#include "Crocodile.h"
#include "Goose.h"
#include "Mammal.h"
#include "Oviparous.h"
#include "Pelican.h"
#include "SeaLion.h"
#include "Whale.h"

using namespace std;



void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
	JavaVM* jvm;                      // Pointer to the JVM (Java Virtual Machine)
	JNIEnv* env;                      // Pointer to native interface
															 //================== prepare loading of Java VM ============================
	JavaVMInitArgs vm_args;                        // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	options[0].optionString = (char*)"-Djava.class.path=";   // where to find java .class
	vm_args.version = JNI_VERSION_1_6;             // minimum Java version
	vm_args.nOptions = 1;                          // number of options
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
																		 //=============== load and initialize Java VM and JNI interface =============
	jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
	delete options;    // we then no longer need the initialisation options.
	if (rc != JNI_OK) {
		// TO DO: error processing...
		cin.get();
		exit(EXIT_FAILURE);
	}
	//=============== Display JVM version =======================================
	cout << "JVM load succeeded: Version ";
	jint ver = env->GetVersion();
	cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

	jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
	if (cls2 == nullptr) {
		cerr << "ERROR: class not found !";
	}
	else {                                  // if class found, continue
		cout << "Class MyTest found" << endl;
		jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
		if (mid == nullptr)
			cerr << "ERROR: method void createZooFile() not found !" << endl;
		else {
			env->CallStaticVoidMethod(cls2, mid);                      // call method
			cout << endl;
		}
	}


	jvm->DestroyJavaVM();
	cin.get();
}



//create an animal subtype, returns an animal pointer to it
Animal* makeAnimal(int trackNum, string name, string type, string subType, int eggs, int nurse) {
	if (subType == "Crocodile") {
		Crocodile* a = new Crocodile(eggs);
		a->trackNumber = trackNum;
		a->name = name;
		return a;

	}
	else if (subType == "Goose") {
		Goose* a = new Goose(eggs);
		a->trackNumber = trackNum;
		a->name = name;
		return a;
	}
	else if (subType == "Pelican") {
		Pelican* a = new Pelican(eggs);
		a->trackNumber = trackNum;
		a->name = name;
		return a;
	}
	else if (subType == "Bat") {
		Bat* a = new Bat(nurse);
		a->trackNumber = trackNum;
		a->name = name;
		return a;
	}
	else if (subType == "Whale") {
		Whale* a = new Whale(nurse);
		a->trackNumber = trackNum;
		a->name = name;
		return a;
	}
	else if (subType == "SeaLion") {
		SeaLion* a = new SeaLion(nurse);
		a->trackNumber = trackNum;
		a->name = name;
		return a;
	}

}


//true if track# already being used in zoo
bool trackNumInUse(vector<Animal*>& zoo, int trackNum)
{
	for (int i = 0; i < zoo.size(); i++) {
		if (zoo[i]->trackNumber == trackNum) {
			return true;
		}
	}
	return false;

}

//prompts user for info to add an animal to the zoo using vector
void AddAnimal(vector<Animal*>& zoo)
{
	int trackNum;
	bool usedTrackNum;
	string name;
	string type;
	string subType;
	int eggs=0;
	int nurse=0;

	cout << "---------------------" << endl;
	cout << "Enter -1 at any time to stop adding the animal." << endl;

	//prompt for and verify track#
	do {
		cout << "Please enter a valid Track#: " << endl;
		cin >> trackNum;

		usedTrackNum = trackNumInUse(zoo, trackNum);
		if (usedTrackNum) {
			cout << "Track# already in use. Please choose another." << endl;
		}

		if (trackNum == -1)
			return;
	} while (!(trackNum >= 1 && trackNum<=999999 && !usedTrackNum));


	//prompt for name
	cout << "Please enter a name: " << endl;
	cin.ignore();
	getline(cin, name);
	if (name == "-1")
		return;


	//prompt for and validate type and subtype
	do {
		cout << "Please enter a valid type: " << endl;
		cin.ignore();
		cin >> type;
		if (type == "-1")
			return;

		//prompt for and validate subtype
		if (type == "Oviparous") {
			do {
				cout << "Please enter a valid sub-type: " << endl;
				cin.ignore();
				cin >>subType;
				if (subType== "-1")
					return;
			} while (!(subType == "Crocodile" || subType == "Goose" || subType == "Pelican"));
		}
		else if (type == "Mammal") {
			do {
				cout << "Please enter a valid sub-type: " << endl;
				cin.ignore();
				cin >> subType;
				if (subType == "-1")
					return;
			} while (!(subType == "Bat" || subType == "Whale" || subType == "SeaLion"));
		}
	} while (!(type=="Oviparous" || type=="Mammal"));


	//Ovi prompts for eggs
	if (type == "Oviparous") {
		do {
			cout << "Please enter the number of eggs: " << endl;
			cin >> eggs;
			if (eggs==-1)
				return;
		} while (!(eggs>= 0));
	}

	//mammal prompts for nurse
	else if (type == "Mammal") {
		do {
			cout << "Please enter the number of nurse: " << endl;
			cin >> nurse;
			if (nurse == -1)
				return;
		} while (!(nurse>= 0));
	}

	//add confirmation
	cout << "Are you sure you wish to add:" << endl;
	Animal* a = makeAnimal(trackNum, name, type, subType, eggs, nurse);
	a->display();
	cout << "Y/N" << endl;
	char confirmation;
	cin >> confirmation;
	if (confirmation == 'Y' || confirmation == 'y') {
		zoo.push_back(a);
		cout << "Animal successfully added." << endl;
	}




}

//prompts user to remove animal from zoo via tracking#
void RemoveAnimal(vector<Animal*>& zoo)
{
	//prompt for tracking#
	int trackingNum;
	cout << "Please enter the tracking number of the animal you wish to remove:" << endl;
	cin >> trackingNum;


	//validate tracking# exists in zoo, if found, saves position in vector
	int location=-1;
	for (auto i = 0; i < zoo.size(); i++) {
		if (zoo[i]->trackNumber == trackingNum)
			location = i;
	}

	if (location == -1) {
		cout << "Invalid tracking number." << endl;
		return;
	}

	//delete confirmation
	else {
		cout << "Are you sure you wish to delete:" << endl;
		zoo[location]->display();
		cout << "Y/N" << endl;
		char confirmation;
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y') {
			delete zoo[location];
			zoo.erase(zoo.begin()+location);
			cout << "Animal successfully deleted." << endl;
		}
	}
}


//load input.txt data into zoo
void LoadDataFromFile(vector<Animal*> &zoo)
{
	//empty zoo
	zoo.clear();


	int trackNum=-1;
	string name;
	string type;
	string subType;
	int eggs;
	int nurse;
	int prevTrackNum;

	//open input.txt
	ifstream fin("input.txt");

	//validate file is open
	if (!fin.is_open()) {
		cout << "File not found" << endl;
	}
	else {

		//read animal info and save into zoo
		while (!fin.eof() ) {
			prevTrackNum = trackNum;//prevents double reading at end of file
			fin >> trackNum;
			fin >> name;
			fin >> type;
			fin >> subType;
			fin >> eggs;
			fin >> nurse;
			if (trackNum == prevTrackNum)
				break;
			zoo.push_back(makeAnimal(trackNum, name, type, subType, eggs, nurse));
		}

		fin.close();
		cout << "Load successful." << endl;
	}
}

//display zoo in table format
void displayAnimalData(vector<Animal*>& zoo) {
	cout << left << setfill(' ') <<
		setw(16) << "Track#" <<
		setw(16) << "Name" <<
		setw(16) << "Type" <<
		setw(16) << "Sub-type" <<
		setw(10) << "Eggs" <<
		setw(10) << "Nurse" <<
		endl;
	for (int i = 0; i < zoo.size(); i++) {
		zoo[i]->display();
	}

}

//save zoo info to input.txt
void SaveDataToFile(vector<Animal*>& zoo)
{
	//open file
	ofstream fout("input.txt");

	//validate file is open
	if (!fout.is_open()) {
		cout << "File not found" << endl;
		return;
	}
	else {

		//loops through zoo to save animal information
		for (int i = 0; i < zoo.size(); i++) {
			if (zoo[i]->type == "Oviparous") {
				Oviparous* temp = (Oviparous*)zoo[i];
				fout << temp->trackNumber<<endl;
				fout << temp->name << endl;
				fout << temp->type << endl;
				fout << temp->subType << endl;
				fout << temp->getNumberOfEggs() << endl;
				fout << "0" << endl;
			}
			else if (zoo[i]->type == "Mammal") {
				Mammal* temp = (Mammal*)zoo[i];
				fout << temp->trackNumber << endl;
				fout << temp->name << endl;
				fout << temp->type << endl;
				fout << temp->subType << endl;
				fout << "0" << endl;
				fout << temp->getNurse() << endl;
			}

		}

		cout << "Save successfully completed." << endl;
	}

}

void DisplayMenu()
{

//display menu to user to select from

	cout << "---------------------" << endl;
	cout << "Main menu:" << endl;
	cout << "1:Load Animal Data" << endl;
	cout << "2:Generate Data" << endl;
	cout << "3:Display Animal Data" << endl;
	cout << "4:Add Record" << endl;
	cout << "5:Delete Record" << endl;
	cout << "6:Save Animal Data" << endl;
	cout << "7:Exit" << endl;
	cout << "---------------------" << endl;
	cout << "Selection: ";
}



int main()
{
	vector <Animal*> zoo;
	int choice=-1;

	do {
		DisplayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			LoadDataFromFile(zoo);
			break;
		case 2:
			//GenerateData();
			break;
		case 3:
			displayAnimalData(zoo);
			break;
		case 4:
			AddAnimal(zoo);
			break;
		case 5:
			RemoveAnimal(zoo);
			break;
		case 6:
			SaveDataToFile(zoo);
			break;
		}



	} while (choice != 7);



	return 0;
}
