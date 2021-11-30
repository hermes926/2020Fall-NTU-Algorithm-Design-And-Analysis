import os


In = "testdata.in" 
Out = "test.out" 
os.system("a.out < %s > %s" %(In,Out))
print("For testcase hi :" )
os.system("checker.exe --public %s %s" %(In, Out))
