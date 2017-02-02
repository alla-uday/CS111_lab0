default :
	gcc -o lab0 lab0.c
check:
	@echo "---------Test1--------"
	printf "Uday \n" | ./lab0 > test1.txt
	printf "Uday \n" | diff - test1.txt
	@echo "---------Test2--------"
	printf "Uday \n" | ./lab0 --output=hello.txt
	printf "Uday \n" | diff - hello.txt
	@echo "---------Test3--------"
	! ./lab0 --input  
	@echo "---------Test4--------"
	./lab0 --input=hello.txt | diff - hello.txt
	@echo "---------Test5--------"
	./lab0 --input=hello.txt --output=test2.txt
	cat test2.txt | diff - hello.txt
	@echo "---------Test6--------"
	! ./lab0 --input=thisfiledoesntexist.txt
	@echo "---------Test7--------"
	! ./lab0 --segfault
	@echo "---------Test8--------"
	! ./lab0 --segfault --catch
	@echo "---------SUCCESSFULL---------"
	$(RM) *~  *.txt

clean:
	$(RM) lab0 *.o *~ *.out *.txt
dist:
	tar -cvzf lab0-404428077.tar.gz lab0.c README Makefile variableInspection.png backtrace.png
