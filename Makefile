
sampleobjects = $(managerobjects) sample_run.o
insertionobjects = $(managerobjects) insertion.o
mergeobjects = $(managerobjects) mergesort.o
bsobjects = $(managerobjects) binarysearch.o
managerobjects = buffer_manager.o file_manager.o

app : mergesort_run bs_run sample_run insertion_run


mergesort_run : $(mergeobjects)
	g++ -std=c++11 -o mergesort_run $(mergeobjects)

mergesort.o : mergesort.cpp
	g++ -std=c++11 -c mergesort.cpp

insertion_run : $(insertionobjects)
	g++ -std=c++11 -o insertion_run $(insertionobjects)

insertion.o : insertion.cpp
	g++ -std=c++11 -c insertion.cpp

bs_run : $(bsobjects)
	g++ -std=c++11 -o bs_run $(bsobjects)

binarysearch.o : binarysearch.cpp
	g++ -std=c++11 -c binarysearch.cpp

sample_run : $(sampleobjects)
	 g++ -std=c++11 -o sample_run $(sampleobjects)

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run
	rm -f bs_run
	rm -f insertion_run
	rm -f mergesort_run
