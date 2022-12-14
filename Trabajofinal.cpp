
#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/**************
***	DEFINES ***
***************/

#define NUM_MONTHS 12
#define NUM_REGIONS 4
#define NUM_SELLERS 3
#define DATA_BIN_FILE "data.bin"

#define TABLE_COL_NAME_SIZE 15
#define TABLE_COL_MONTH_SIZE 8 

/*************
***	MACROS ***
**************/

#define GetSalesSumAmountByRegion(data, region) GetSalesSumAmount(data, region, -1, -1)
#define GetSalesSumAmountBySeller(data, seller) GetSalesSumAmount(data, -1, seller, -1)
#define GetSalesSumAmountByMonth(data, month) GetSalesSumAmount(data, -1, -1, month)
#define GetSalesSumAmountByRegionSeller(data, region, seller) GetSalesSumAmount(data, region, seller, -1)
#define GetSalesSumAmountByRegionMonth(data, region, month) GetSalesSumAmount(data, region, -1, month)
#define GetSalesSumAmountBySellerMonth(data, seller, month) GetSalesSumAmount(data, -1, seller, month)

/*************
***	USINGS ***
**************/

using namespace std;

using Data =
array<		   // Regions
	array<	   // Sellers
	array< // Months
	int, NUM_MONTHS>,
	NUM_SELLERS>,
	NUM_REGIONS>;

using vectordventas = vector<int>;

struct Best
{
	unsigned count{};
	array<int, NUM_MONTHS> list{};
};

/*****************
***	PROTOTYPES ***
******************/

void LoadTxtFile();
bool LoadBinData(Data&, vectordventas&);
void SaveBinData(Data&, const vectordventas&);
void AddSale(Data&, vectordventas&, int, int, int, int);

string GetMonthName(int month);
string GetSellerName(int seller);

int GetSalesSumAmount(const Data&, int = -1, int = -1, int = -1);

Best GetBestSellersByRegion(const Data&, int);
Best GetBestMonthsByRegion(const Data&, int);

void PrintSellersNames(const Best);
void PrintMonths(const Best);
void PrintStatistics(const Data&, const vectordventas&, int = -1);
void PrintTable(const Data&, int);

/***********
***	MAIN ***
************/

int main()
{
	Data data{};
	vectordventas mejorvendedor{};

	// LoadTxtFile();
	LoadBinData(data, mejorvendedor);

	PrintStatistics(data, mejorvendedor);

	return 0;
}

/****************
***	FUNCTIONS ***
*****************/

void LoadTxtFile()
{
	cout << "Reading sales information from the input stream.\n";

	Data data;
	vectordventas mejorvendedor{};

	for (int region{}, seller{}, month{}, amount{}; cin >> region >> seller >> month >> amount;)
		AddSale(data,mejorvendedor, region, seller, month, amount);

	SaveBinData(data,mejorvendedor);
}

bool LoadBinData(Data& data, vectordventas &mejorvendedor)
{
	ifstream file;
	try
	{
		file.open(DATA_BIN_FILE, ios::in | ios::binary);

		unsigned sales_count{};
		file.read(reinterpret_cast<char*>(&sales_count), sizeof(unsigned));

		for (unsigned i{}; i < sales_count; i++)
		{
			int amount{};
			file.read(reinterpret_cast<char*>(&amount), sizeof(int));
			mejorvendedor.push_back(amount);
		}

		file.read(reinterpret_cast<char*>(&data), sizeof(data));

		file.close();
	}
	catch (int error)
	{
		if (file.is_open())
			file.close();
		return false;
	}

	return true;
}

void SaveBinData(Data& data,const vectordventas& mejorvendedor)
{
	ofstream file;
	file.open(DATA_BIN_FILE, ios::out | ios::binary);

	unsigned sales_count = mejorvendedor.size();
	file.write(reinterpret_cast<char*>(&sales_count), sizeof(unsigned));

	for (auto amount : mejorvendedor)
		file.write(reinterpret_cast<char*>(&amount), sizeof(int));

	file.write(reinterpret_cast<char*>(&data), sizeof(data));

	file.close();
}

void AddSale(Data& data, vectordventas& mejorvendedor, int region, int seller, int month, int amount)
{
	data.at(region - 1).at(seller - 1).at(month - 1) += amount;

	if (region == 1 && seller == 1)
		mejorvendedor.push_back(amount);
}

string GetRegionName(int region)
{
	switch (region)
	{
	case 1:
		return "North";
	case 2:
		return "West";
	case 3:
		return "South";
	case 4:
		return "East";
	default:
		return "Not defined";
	}
}

string GetMonthName(int month)
{
	switch (month)
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "Not defined";
	}
}

string GetSellerName(int seller)
{
	switch (seller)
	{
	case 1:
		return "Roger Caceres";
	case 2:
		return "German Ceballos";
	case 3:
		return "Jeronimo Fermepin Galdo";
	case 4:
		return "Pilar Fernandez";
	case 5:
		return "Nicolas Filippi Farmar";
	case 6:
		return "Enrique Marques";
	case 7:
		return "Tobias Sailler Quintana";
	case 8:
		return "Curt Venator Rauch";
	default:
		return "Not defined";
	}
}



int GetSalesSumAmount(const Data &data, int region, int seller, int month)
{
	int sum{};
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : NUM_REGIONS); ix_region++)
		for (int ix_seller{seller != -1 ? seller : 0}; ix_seller < ((seller != -1) ? seller + 1 : NUM_SELLERS); ix_seller++)
			for (int ix_month{month != -1 ? month : 0}; ix_month < ((month != -1) ? month + 1 : NUM_MONTHS); ix_month++)
				sum += data.at(ix_region).at(ix_seller).at(ix_month);
	return sum;
}

int GetSalesMaxAmount(const Data &data, int region, int seller, int month)
{
	int max{};
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : (int)data.size()); ix_region++)
		for (int ix_seller{seller != -1 ? seller : 0}; ix_seller < ((seller != -1) ? seller + 1 : (int)data.at(ix_region).size()); ix_seller++)
			for (int ix_month{month != -1 ? month : 0}; ix_month < ((month != -1) ? month + 1 : (int)data.at(ix_region).at(ix_seller).size()); ix_month++)
				if (data.at(ix_region).at(ix_seller).at(ix_month) > max)
					max = data.at(ix_region).at(ix_seller).at(ix_month);
	return max;
}

Best GetBestSellersByRegion(const Data &data, int region)
{
	Best bestSellers{};
	int maxAmount{};

	for (int ix_seller{}; ix_seller < data.at(region).size(); ix_seller++)
	{
		int max = GetSalesSumAmountByRegionSeller(data, region, ix_seller);
		if (max > maxAmount)
		{
			maxAmount = max;
			bestSellers.count = 0;
			bestSellers.list.fill(0);
		}
		if (max >= maxAmount)
		{
			bestSellers.list.at(bestSellers.count) = ix_seller;
			bestSellers.count++;
		}
	}

	return bestSellers;
}

Best GetBestMonthsByRegion(const Data &data, int region)
{
	Best bestMonths{};
	array<int, NUM_MONTHS> maxAmount{};

	for (int ix_seller{}; ix_seller < NUM_SELLERS; ix_seller++)
		for (int ix_month{}; ix_month < NUM_MONTHS; ix_month++)
			maxAmount[ix_month] += GetSalesSumAmount(data, region, ix_seller, ix_month);

	int max{};
	for (int ix_month{}; ix_month < NUM_MONTHS; ix_month++)
	{
		if (maxAmount.at(ix_month) > max)
		{
			max = maxAmount.at(ix_month);
			bestMonths.count = 0;
			bestMonths.list.fill(0);
		}
		if (maxAmount.at(ix_month) >= max)
		{
			bestMonths.list.at(bestMonths.count) = ix_month;
			bestMonths.count++;
		}
	}

	return bestMonths;
}

void PrintSellersNames(const Best bestSellers)
{
	cout << "[";
	for (int ix{}; ix < bestSellers.count; ix++)
	{
		cout << (ix > 0 ? ", " : "") << GetSellerName(bestSellers.list.at(ix) + 1);
	}
	cout << "]";
}

void PrintMonths(const Best bestMonths)
{
	cout << "[";
	for (unsigned ix{}; ix < bestMonths.count; ix++)
		cout << (ix > 0 ? ", " : "") << GetMonthName(bestMonths.list.at(ix) + 1);
	cout << "]";
}

void PrintStatistics(const Data& data, const vectordventas& mejorvendedor, int region)
{
	cout << "Sales for the region 1, seller 1: [";
	for (unsigned ix{}; ix < mejorvendedor.size(); ix++)
	{
		cout << (ix > 0 ? ", " : "") << mejorvendedor.at(ix);
	}
	cout << "]\n\n";
	for (int ix_region{ region != -1 ? region : 0 }; ix_region < ((region != -1) ? region + 1 : NUM_REGIONS); ix_region++)
	{
		cout << "Statistics for Region <" << GetRegionName(ix_region + 1) << ">:\n";
		cout << "\tMax amount of the year: $" << GetSalesSumAmountByRegion(data, ix_region) << "\n";
		cout << "\tBest seller/s of the year: ";
		PrintSellersNames(GetBestSellersByRegion(data, ix_region));
		cout << "\n";
		cout << "\tBest months/s of the year: ";
		PrintMonths(GetBestMonthsByRegion(data, ix_region));
		cout << "\n";
		cout << "\n";
		PrintTable(data, ix_region);
	}
}

string FixedLengthString(string txt, unsigned length)
{
	string ret{};
	for (unsigned i{}; i < length; i++)
		ret += txt.length() > i ? txt[i] : ' ';
	return ret;
}

void PrintTable(const Data& data, int ix_region)
{
	// Print headers
	cout << "\t" << FixedLengthString("Seller", TABLE_COL_NAME_SIZE);
	for (int i{}; i < NUM_MONTHS; i++)
		cout << " | " << FixedLengthString(GetMonthName(i + 1), TABLE_COL_MONTH_SIZE);

	cout << " | " << FixedLengthString("Total", TABLE_COL_MONTH_SIZE) << "\n\t";

	// Print div line
	for (int i{}; i < (TABLE_COL_NAME_SIZE + 13 * (TABLE_COL_MONTH_SIZE + 3)); i++)
		cout << "-";
	cout << "\n";

	// Print amounts by seller
	for (int ix_seller{}; ix_seller < NUM_SELLERS; ix_seller++)
	{
		cout << "\t" << FixedLengthString(GetSellerName(ix_seller + 1), TABLE_COL_NAME_SIZE);
		for (int ix_month{}; ix_month < NUM_MONTHS; ix_month++)
		{
			cout << " | $" << FixedLengthString(to_string(GetSalesSumAmount(data, ix_region, ix_seller, ix_month)), (TABLE_COL_MONTH_SIZE - 1));
		}
		cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegionSeller(data, ix_region, ix_seller)), (TABLE_COL_MONTH_SIZE - 1)) << "\n";
	}

	// Print div line
	cout << "\t";
	for (int i{}; i < (TABLE_COL_NAME_SIZE + 13 * (TABLE_COL_MONTH_SIZE + 3)); i++)
		cout << "-";
	cout << "\n";

	// Print Total amounts
	cout << "\t" << FixedLengthString("Total", TABLE_COL_NAME_SIZE);
	for (int ix_month{}; ix_month < NUM_MONTHS; ix_month++)
	{
		cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegionMonth(data, ix_region, ix_month)), (TABLE_COL_MONTH_SIZE - 1));
	}
	cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegion(data, ix_region)), (TABLE_COL_MONTH_SIZE - 1)) << "\n";

	cout << "\n";
}
