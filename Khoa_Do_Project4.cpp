/*
Khoa Dang Do
Larry Yarbrough
CSC 134-03
4 May 2016
Project 3: Postal Barcode
*/

/*Project 3 + extra credit code. This time I will modulize my main function into several smaller functions*/

#include <iostream>
#include <string>
#include <fstream> // reading file
using namespace std;

// making global constant
const double LETTER_RATE = 0.49, ENVELOPE_RATE = 0.98, PARCEL_RATE = 2.54, // standard prices of mailing types
		     LETTER_ADD = 0.22, ENVELOPE_ADD = 0.22, PARCEL_ADD = 0.20;    // addtional payments when overweighed
		     
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/		     
		     
// display menu
void displayMenu ();

 // calculate checksum digit
int checksumDigitCal (int d1, int d2, int d3, int dt4, int d5); 

// modular functions to accept each digit, calculate and return the barcode forms of the 5 digits and the check digit
string encodedValue1 (int d1);
string encodedValue2 (int d2);
string encodedValue3 (int d3);
string encodedValue4 (int d4);
string encodedValue5 (int d5);
string encodedValue6 (int d6);

// calculate and return postage due
double postageCalculating (int op_tion, double weighT);

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
		     
int main ()
{
	string name = "", streetAddress = "", city = "", state = "", junkChar = "" /*read space and blank lines in a file*/,
		   barcode1 = "",barcode2 = "", barcode3 = "", barcode4 = "", barcode5 = "", barcode6 = ""; // barcodes of 5-digit zipcode and check digit
	int zipcode, menuChoice, option /*mailing item options*/, num, digit1, digit2, digit3, digit4, digit5, checkDigit;
	double weight, postage_Due, totalDue2 = 0;
	
	cout << "Welcome to the Mailing Label Printing System\n" << endl;
	displayMenu (); // function call to display menu
	cin >> menuChoice;
		// validate menu choice
		while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3)
		{	cout << "Invalid choice, please enter a valid choice: ";
			cin >> menuChoice;	}
			
	// I found do-while the best statement to use in this project. Switch, if/esle if, while will be built around do-while statement
	do
	{
		if (menuChoice == 1) // do this entire code if menu choice entered at the beginning = 1
		{
			cin.ignore(); // ignore null character when the user has enter a number as a menu choice before enter his/her name 
			cout << endl;
			// user's inputs
			cout << "Enter name: ";
			getline(cin, name);
			cout << "Enter street address: ";
			getline(cin, streetAddress);
			cout << "Enter city: ";
			getline(cin, city);
			cout << "Enter state: ";
			getline(cin, state);
			cout << "Enter zipcode: ";
			cin >> zipcode;
			cout << "Enter 1 for letter, 2 for envelope, 3 for parcel: ";
			cin >> option;
	
			// validate mailing item option
			// this code always makes sure the number entered will be 1, 2, or 3 
			// so I can use switch after this without worrying it can cause errors and without default case
			while (option != 1 && option != 2 && option != 3)
			{	cout << "Invalid option of item type, please enter a valid option: ";
				cin >> option;	}
			
			// ask and validate the weight of user's mailing item	
			cout << "Enter weight in ounces: ";
			cin >> weight;
				while (weight < 0) // right here is in case if user enters a nagative number of weight
				{	cout << "Invalid weight, please enter positive number: ";
					cin >> weight;	}
			
			// function call to calculate postage due	
			postage_Due = postageCalculating (option, weight);
			
			// separate 5 digits
    		digit5 = zipcode % 10;
			num = zipcode / 10;
			digit4 = num % 10;
			num /= 10;
			digit3 = num % 10;
			num /= 10;
			digit2 = num % 10;
			digit1 = num /10;
			// functiuon call to calculate the check digit
			checkDigit = checksumDigitCal (digit1, digit2, digit3, digit4, digit5);
			
			// function calls to encode the digits
			barcode1 = encodedValue1 (digit1);
			barcode2 = encodedValue2 (digit2);
			barcode3 = encodedValue3 (digit3);
			barcode4 = encodedValue4 (digit4);
			barcode5 = encodedValue5 (digit5);
			barcode6 = encodedValue6 (checkDigit);
			
			// display mailing label(s)
			cout << endl << "**************************$" << postage_Due << endl << endl; 
			cout << name << endl;
			cout << streetAddress << endl;
			cout << city << "  " << state << " " << zipcode << endl << endl;
			cout << "|" << barcode1 << barcode2 << barcode3 << barcode4 << barcode5 << barcode6 << "|";
		}
		
		else if (menuChoice == 2) // do this entire code if menu choice entered at the beginning = 2
		{
			cin.ignore(); // ignore null char when enter menu choice number at the beginning
			ifstream fileReader; // create file stream
			fileReader.open("Mailings.txt"); // open file named Mailings.txt
			ofstream fileOutput; // create file stream
			fileOutput.open("DataStorage.txt"); // open file named DataStorage.txt

			// read and store values in variables
			while (getline(fileReader, name))
			{
				getline(fileReader, streetAddress);
				getline(fileReader, city);
				getline(fileReader, state);
				fileReader >> zipcode;
				fileReader >> option;
				fileReader >> weight;
				getline(fileReader, junkChar); // read the end-line char and blank char at the end of each person's information
				getline(fileReader, junkChar);
				
				// function call to calculate postage due
				postage_Due = postageCalculating (option, weight);
				
				// accumualte the total postage dues in the txt file,
				// **note: there is no totalDue1, I just name it totalDue2 (2 means it happens when menu choice = 2
				totalDue2 += postage_Due;
				
				// separate 5 digits
				digit5 = zipcode % 10;
				num = zipcode / 10;
				digit4 = num % 10;
				num /= 10;
				digit3 = num % 10;
				num /= 10;
				digit2 = num % 10;
				digit1 = num /10;
				// function call to calculate the check digit
				checkDigit = checksumDigitCal (digit1, digit2, digit3, digit4, digit5);
				
				// function calls to encode the digits
				barcode1 = encodedValue1 (digit1);
				barcode2 = encodedValue2 (digit2);
				barcode3 = encodedValue3 (digit3);
				barcode4 = encodedValue4 (digit4);
				barcode5 = encodedValue5 (digit5);
				barcode6 = encodedValue6 (checkDigit);
				
				// display mailing label(s)
				cout << endl << endl;
				cout << endl << "**************************$" << postage_Due << endl << endl; 
				cout << name << endl;
				cout << streetAddress << endl;
				cout << city << "  " << state << " " << zipcode << endl << endl;
				cout << "|" << barcode1 << barcode2 << barcode3 << barcode4 << barcode5 << barcode6 << "|";
			
				// extra credit code, write the mailing labels into another file
				// write the mailing labels into a text file name DataStorage.txt
				fileOutput << endl << endl;
				fileOutput << "**************************$" << postage_Due << endl << endl;
				fileOutput << name << endl;
				fileOutput << streetAddress << endl;
				fileOutput << city << "  " << state << " " << zipcode << endl << endl;
				fileOutput << "|" << barcode1 << barcode2 << barcode3 << barcode4 << barcode5 << barcode6 << "|";
				// line 131 to 182 will repeat and output continuously until there is no file left in the txt file	
			}
			// display total due in the txt file in DataStorage
			fileOutput << endl << endl << "Total cost of all the postage in text file is " << "$" << totalDue2 << "." << endl;
			// close file
			fileReader.close (); 
			fileOutput.close();
		}
		
		else if (menuChoice == 3) // do this if menu choice entered at the beginning = 3
		{
			cin.ignore();
			// display total due in the txt file, I want to bring this to the end after user hits 3, just for a nice output format
			cout << endl << "Total cost of all the postage in text file is " << "$" << totalDue2 << "." << endl;
			cout << "Thank you. Closing program." << endl;
			return 0; // if user hits 3, program will return to 0 and program ends right here, so no need 'return 0' at the final line of main function
		}
		
		// repeat the program if the the user would like to do so
		cout << endl << endl << endl;
		displayMenu ();
		cin >> menuChoice;
			// validate menu choice
			while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3)
			{	cout << "Invalid choice, please enter a valid choice: ";
				cin >> menuChoice;	}
	}	while (menuChoice == 1 || menuChoice == 2 || menuChoice == 3); // this loop will happen on and on until user hits 3 to exit
}																			// and display total dues in the txt file	

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

void displayMenu ()
{
	cout << "1 - Single Mailing" << endl;
	cout << "2 - Multiple Mailings" << endl;
	cout << "3 - Quit\n" << endl;
	cout << "Enter your choice: ";
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

double postageCalculating (int op_tion, double weighT)
{
	double weight, postageDue;
	
	switch (op_tion)
			{
				case 1: // dues for letters
				if (weighT >= 0.00 && weighT <= 1.00) // underweighed
					{ postageDue = LETTER_RATE; } 
				else if (weighT > 1.00 && weighT == static_cast<int>(weighT)) // overweighed but no partial ounce (decimal) is added (5.0 = 5)
					{ postageDue = LETTER_RATE + (static_cast<int>(weighT) - 1.00) * LETTER_ADD; }
				else if (weighT > 1.00 && weighT != static_cast<int>(weighT)) // overwieghed and partical ounce (decimal) is added (5.4 != 5)
					{ postageDue = LETTER_RATE + static_cast<int>(weighT) * LETTER_ADD; }
					break;                                                                   
				
				case 2: // dues for evenlopes
				if (weighT >= 0.00 && weighT <= 1.00)
					{ postageDue = ENVELOPE_RATE; } 
				else if (weighT > 1.00 && weighT == static_cast<int>(weighT))
					{ postageDue = ENVELOPE_RATE + (static_cast<int>(weighT) - 1.00) * ENVELOPE_ADD; }
				else if (weighT > 1.00 && weighT != static_cast<int>(weighT))
					{ postageDue = ENVELOPE_RATE + static_cast<int>(weighT) * ENVELOPE_ADD; }
					break;
				
				case 3: // dues for parcels
				if (weighT >= 0.00 && weighT <= 3.00)
					{ postageDue = PARCEL_RATE; } 
				else if (weighT > 3.00 && weighT == static_cast<int>(weighT))
					{ postageDue = PARCEL_RATE + (static_cast<int>(weighT) - 3.00) * PARCEL_ADD; } 
				else if (weighT > 3.00 && weight != static_cast<int>(weighT))
					{ postageDue = PARCEL_RATE + (static_cast<int>(weighT) - 2.00) * PARCEL_ADD; }
					break;
			}	
			
	return postageDue;	// return the value to main function		
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

int checksumDigitCal (int d1, int d2, int d3, int d4, int d5)
{
	int checksum;
	
	checksum = 10 - ((d1 + d2 + d3 + d4 + d5) % 10);
	
	return checksum; // return the value to main function
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

string encodedValue1 (int d1)
{
	string barcodeA;
	
	switch (d1)
			{	case 1: barcodeA = ":::||"; break;
				case 2: barcodeA = "::|:|"; break;
				case 3: barcodeA = "::||:"; break;
				case 4: barcodeA = ":|::|"; break;
				case 5: barcodeA = ":|:|:"; break;
				case 6: barcodeA = ":||::"; break;
				case 7: barcodeA = "|:::|"; break;
				case 8: barcodeA = "|::|:"; break;
				case 9: barcodeA = "|:|::"; break;   }
	
	return barcodeA; // return the value to main function
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

string encodedValue2 (int d2)
{
	string barcodeB;
	
	switch (d2)
			{	case 1: barcodeB = ":::||"; break;
				case 2: barcodeB = "::|:|"; break;
				case 3: barcodeB = "::||:"; break;
				case 4: barcodeB = ":|::|"; break;
				case 5: barcodeB = ":|:|:"; break;
				case 6: barcodeB = ":||::"; break;
				case 7: barcodeB = "|:::|"; break;
				case 8: barcodeB = "|::|:"; break;
				case 9: barcodeB = "|:|::"; break;   }
				
	return barcodeB; // return the value to main function
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

string encodedValue3 (int d3)
{
	string barcodeC;
	
	switch (d3)
			{	case 1: barcodeC = ":::||"; break;
				case 2: barcodeC = "::|:|"; break;
				case 3: barcodeC = "::||:"; break;
				case 4: barcodeC = ":|::|"; break;
				case 5: barcodeC = ":|:|:"; break;
				case 6: barcodeC = ":||::"; break;
				case 7: barcodeC = "|:::|"; break;
				case 8: barcodeC = "|::|:"; break;
				case 9: barcodeC = "|:|::"; break;   }
				
	return barcodeC; // return the value to main function
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

string encodedValue4 (int d4)
{
	string barcodeD; 
	
	switch (d4)
			{	case 1: barcodeD = ":::||"; break;
				case 2: barcodeD = "::|:|"; break;
				case 3: barcodeD = "::||:"; break;
				case 4: barcodeD = ":|::|"; break;
				case 5: barcodeD = ":|:|:"; break;
				case 6: barcodeD = ":||::"; break;
				case 7: barcodeD = "|:::|"; break;
				case 8: barcodeD = "|::|:"; break;
				case 9: barcodeD = "|:|::"; break;   }
				
	return barcodeD; // return the value to main function
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

string encodedValue5 (int d5)
{
	string barcodeE;
	
	switch (d5)
			{	case 1: barcodeE = ":::||"; break;
				case 2: barcodeE = "::|:|"; break;
				case 3: barcodeE = "::||:"; break;
				case 4: barcodeE = ":|::|"; break;
				case 5: barcodeE = ":|:|:"; break;
				case 6: barcodeE = ":||::"; break;
				case 7: barcodeE = "|:::|"; break;
				case 8: barcodeE = "|::|:"; break;
				case 9: barcodeE = "|:|::"; break;   }
				
	return barcodeE; // return the value to main function
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

string encodedValue6 (int d6)
{
	string barcodeF;
	
	switch (d6)
			{	case 1: barcodeF = ":::||"; break;
				case 2: barcodeF = "::|:|"; break;
				case 3: barcodeF = "::||:"; break;
				case 4: barcodeF = ":|::|"; break;
				case 5: barcodeF = ":|:|:"; break;
				case 6: barcodeF = ":||::"; break;
				case 7: barcodeF = "|:::|"; break;
				case 8: barcodeF = "|::|:"; break;
				case 9: barcodeF = "|:|::"; break;   }
				
	return barcodeF; // return the value to main function
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
