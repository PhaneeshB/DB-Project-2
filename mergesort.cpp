//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include "constants.h"
#include <bits/stdc++.h>

using namespace std;
FileManager fm;
// int current_buffer_occupancy
// int disk_accesses = 0;

void display_page_content(PageHandler page)
{
	// cout << "The content of the page doesn't include the last integer printed" << endl;
	cout << "Page Number : " << page.GetPageNum() << endl;
	
	int elements_in_page = (int) PAGE_SIZE/sizeof(int);
	int* num = (int*) page.GetData();
	for (int i = 0; i < elements_in_page; i++)
	{

		if (num[i] == INT32_MIN)
		{
			cout << "This was the last element in the page" << endl;
			return;
		}
		cout << "ele_num : " << i << " : " << num[i] << endl;
	}
	num = NULL;
}

bool is_page_full(PageHandler page)
{
	int elements_in_page = (int) PAGE_SIZE/sizeof(int);
	int* num = (int*) page.GetData();
	bool flag = false;
	if (num[elements_in_page -1] == INT32_MIN)
	{
		flag = true;
	}
	num = NULL;
	return flag;
}

void display_file_content(FileHandler file)
{
	int total_pages_in_file = file.LastPage().GetPageNum() + 1;
	PageHandler page = file.FirstPage();
	for(int i=0; i < total_pages_in_file; i++)
	{
		display_page_content(page);
		if(i == total_pages_in_file - 1)
		{
			continue;
		}
		int num = page.GetPageNum();
		page = file.NextPage(page.GetPageNum());
		file.UnpinPage(num);
		
		// try
		// {
		// 	page = file.NextPage(page.GetPageNum());
		// }
		// catch(const InvalidPageException& e)
		// {
		// 	std::cerr << e.what() << '\n';
		// 	// cout << ''
		// }
		
	}
	file.UnpinPage(page.GetPageNum());
}


int get_number_of_elements_in_page(PageHandler page)
{
	//can be optimized to do it in logn time
	int * arr = (int*) page.GetData();
	int elements_in_page = (int) PAGE_SIZE/sizeof(int);
	for (int i = 0; i < elements_in_page; i++)
	{
		if(arr[i] == INT32_MIN)
		{
			return i;
		}
	}
	throw "No INT_MIN IN THE PAGE!!";
}


void bs_in_one_page(PageHandler page, int num)
{
	int* arr = (int*) page.GetData();
}

void sort_copy_page(PageHandler page_input, PageHandler page_output)
{
	int* arr = (int*) page_input.GetData();
	int n = get_number_of_elements_in_page(page_input);
	int val_arr[n];
	for( int i = 0; i <n; i++)
	{
		val_arr[i] = arr[i];
		// memcpy(&val_arr[i], &arr[i], sizeof(int));
	}
	sort(val_arr, val_arr + n);
	int* op_arr  =(int*) page_output.GetData();

	// Do we really need to copy all the elements in the 
	// other file one by one??
	for(int i = 0 ; i < n; i++)
	{
		op_arr[i] = val_arr[i];
		// memcpy(&op_arr[i], &arr[i], sizeof(int));
	}
	op_arr[n] = INT32_MIN;

}
int main() {

	// FileManager fm;
    // char path_input[] = "./testcases/merge_sort/sort_input1.txt";
    char path_input[] = "./testcases/checking/unsorted.txt";

	//Check if it exists.
    // char path_output[] = "./testcases/merge_sort/sort_output_computed1.txt";
    char path_output[] = "./testcases/checking/sort_output_computed1.txt";
    
	char test[] = "./testcases/checking/merge_input1_test.txt";
    // char test[] = "./testcases/checking/test.txt";	
	
    FileHandler file_input = fm.OpenFile(path_input);
    // FileHandler file_output = fm.CreateFile(path_output);
    FileHandler file_output;
	
	// Should only be done at the beginning ot ensure that outputfile is new
	try
	{
		file_output = fm.CreateFile(path_output);
	}
	catch(const InvalidFileException& e)
	{
		// std::cerr << e.what() << '\n';
		fm.DestroyFile(path_output);
		file_output = fm.CreateFile(path_output);
	}
    
	FileHandler file_test = fm.OpenFile(test);
    // display_file_content(file_output);

    // Given a file with sorted pages 

    //given one file with unsorted pages sort the pages create a new file with sorted pages
    
    // display_file_content(file_input);

    // display_page_content(file_test.FirstPage());

	// sort a page in the file 
	fm.PrintBuffer();
	int total_pages = file_input.LastPage().GetPageNum() + 1;
	file_input.UnpinPage(total_pages - 1);

	for( int i = 0; i < total_pages; i++)
	{
		PageHandler page_input = file_input.PageAt(i);
		PageHandler page_output = file_output.NewPage();
		// fm.PrintBuffer();

		sort_copy_page(page_input, page_output);
		// fm.PrintBuffer();

		// display_page_content(page_input);
		file_input.UnpinPage(page_input.GetPageNum());
		// fm.PrintBuffer();

		// display_page_content(page_output);
		file_output.FlushPage(page_output.GetPageNum());
		// fm.PrintBuffer();
		// display_file_content(file_output);

	}


	// PageHandler page_input = file_input.FirstPage();
	// PageHandler page_output = file_output.NewPage();
	// fm.PrintBuffer();

	// sort_copy_page(page_input, page_output);
	// fm.PrintBuffer();

	// display_page_content(page_input);
	// file_input.UnpinPage(page_input.GetPageNum());
	// fm.PrintBuffer();

	// display_page_content(page_output);
	// file_output.FlushPage(page_output.GetPageNum());
	// fm.PrintBuffer();
	// display_file_content(file_output);

	// file_output.FlushPage(file_output.LastPage().GetPageNum());

	// display_page_content(file_output.LastPage());
	fm.PrintBuffer();


}