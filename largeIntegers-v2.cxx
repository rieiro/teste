
#include <iostream>
#include <string>

class largeInteger
{
	public:
	
	largeInteger add(const largeInteger&,const largeInteger&);
	largeInteger sub(const largeInteger&,const largeInteger&);
	largeInteger mult(const largeInteger&,const largeInteger&);

  bool areEqual(const largeInteger&, const largeInteger&);
  
	int  getSize() const;
	void print() const;
	void set(const largeInteger);
	void set(std::string);
    
  largeInteger();
  largeInteger(const largeInteger&);
	largeInteger(std::string);
	~largeInteger();
	
	private:
	void addDigits(const int*,int*,int);
	largeInteger multiply_OLD(const largeInteger&,const largeInteger&);
	largeInteger multiply(const largeInteger&,const largeInteger&);
	largeInteger addAbsValue(const largeInteger&, const largeInteger&);
	bool isAbsFirstGreaterOrEqualSecond(const largeInteger&, const largeInteger&);
	void borrowOne(int* ,int);
	largeInteger subtractAbsFirstFromSecond(const largeInteger&, const largeInteger&);
	void parseStringAndStoreInNumber(std::string);
	void setIntegersToZero(int*,const int);
	
	bool isPositive;
	int *number;
	int numberOfDigits;
};

bool largeInteger::areEqual(const largeInteger& a, const largeInteger& b)
{
	if ( a.isPositive != b.isPositive ) return false;
	else if (a.numberOfDigits != b.numberOfDigits ) return false;
	else
	{
   for (int i=0;i<a.numberOfDigits;i++)
   {
		 if (a.number[i] != b.number[i]) return false;
	 }		
		
	}
	
return true;	
}

void largeInteger::setIntegersToZero(int* ptr,const int size)
{
	for (int i=0; i< size ; i++) ptr[i] = 0;
}

largeInteger largeInteger::multiply(const largeInteger& a,const largeInteger& b)
{
  int numberOfDigitsResult = a.numberOfDigits + b.numberOfDigits + 1;
  int *temp;
  int *result;
  largeInteger c;
  int nextDecimal = 0;
  int currentDigit = 0;
  int tempInt = 0;
  int powerOfTen = 0;
  int i,j;
   
  result = new int[numberOfDigitsResult]; 
  temp = new int[numberOfDigitsResult];
    
  setIntegersToZero(temp,numberOfDigitsResult);
  setIntegersToZero(result,numberOfDigitsResult);      
  
  for (i=0; i < b.numberOfDigits;i++)
  {
	   
	   for ( j=0; j < a.numberOfDigits; j++)
     {   		
			
			for ( powerOfTen=0; powerOfTen < i ;powerOfTen++) { temp[powerOfTen] = 0; }
						
			tempInt = ( a.number[j] * b.number[i] );
			currentDigit = tempInt % 10;
			
			temp[ j + powerOfTen ] = (( currentDigit + nextDecimal) < 10 ? currentDigit + nextDecimal : (currentDigit + nextDecimal) % 10 );
		  nextDecimal = tempInt / 10 + ( currentDigit + nextDecimal) / 10;
		  
		 }
		 if ( nextDecimal != 0 ) 
		 {
			 temp[ j + powerOfTen ] = nextDecimal;
	     nextDecimal = 0;
	   }
	   //temp[] complete, ready to sum in result
	   
	   addDigits(temp,result,numberOfDigitsResult);
	   setIntegersToZero(temp,numberOfDigitsResult);	  
	}
    
  while ( result[numberOfDigitsResult - 1] == 0) numberOfDigitsResult--;
  
  delete []c.number;
    
  c.number = new int[numberOfDigitsResult];
  for (int i = 0; i < numberOfDigitsResult; i++ ) c.number[i] = result[i];
  c.numberOfDigits = numberOfDigitsResult;
  
  delete []temp;
  delete []result;
     
  return c;
}

largeInteger largeInteger::multiply_OLD(const largeInteger& a,const largeInteger& b)
{
  int numberOfDigitsResult = a.numberOfDigits + b.numberOfDigits + 1;
  int **temp;
  int *result;
  largeInteger c;
  int nextDecimal = 0;
  int currentDigit = 0;
  int tempInt = 0;
  int powerOfTen = 0;
  int i,j;
   
  result = new int[numberOfDigitsResult]; 
  temp = new int*[b.numberOfDigits];
    
  for (i=0;i<b.numberOfDigits;i++)
  {
	  temp[i] = new int[numberOfDigitsResult];
	  for ( j=0; j< numberOfDigitsResult; j++) temp[i][j] = 0;
	}
    
  for (i=0; i<numberOfDigitsResult; i++) result[i] = 0;
  
  for (i=0; i < b.numberOfDigits;i++)
  {
	   
	   for ( j=0; j < a.numberOfDigits; j++)
     {   		
			
			for ( powerOfTen=0; powerOfTen < i ;powerOfTen++) { temp[i][powerOfTen] = 0; }
						
			tempInt = ( a.number[j] * b.number[i] );
			currentDigit = tempInt % 10;
			
			temp[i][ j + powerOfTen ] = ((currentDigit+nextDecimal) < 10? currentDigit + nextDecimal: (currentDigit + nextDecimal) % 10 );
		  nextDecimal = tempInt / 10 + ( currentDigit + nextDecimal) / 10;
		  
		 }
		 if ( nextDecimal != 0 ) 
		 {
			 temp[i][ j + powerOfTen ] = nextDecimal;
	     nextDecimal = 0;
	   }
	   //temp[i] complete, ready to sum in result
	   
	   addDigits(temp[i],result,numberOfDigitsResult);
	  	  
	}
    
  while ( result[numberOfDigitsResult - 1] == 0) numberOfDigitsResult--;
  
  delete []c.number;
    
  c.number = new int[numberOfDigitsResult];
  for (int i = 0; i < numberOfDigitsResult; i++ ) c.number[i] = result[i];
  c.numberOfDigits = numberOfDigitsResult;
  
  delete []temp;
  delete []result;
     
  return c;
}

void largeInteger::addDigits(const int* a,int* b,int numDigits)
{
	int nextDecimal = 0;
	for (int i=0; i< numDigits; i++)
	{
		int tempInt;
		tempInt = a[i] + b[i] + nextDecimal;
		
		b[i] = ((tempInt < 10)? tempInt : tempInt % 10);
		nextDecimal = tempInt / 10;
	}
	
}

largeInteger largeInteger::mult(const largeInteger& a,const largeInteger& b)
{
	if (isAbsFirstGreaterOrEqualSecond(a,b)) 
	{
	largeInteger c(multiply(a,b));
	if ( a.isPositive == b.isPositive ) c.isPositive = true; else c.isPositive = false;
	return c;
	}
	else 
	{
	largeInteger c(multiply(b,a));
	if ( a.isPositive == b.isPositive ) c.isPositive = true; else c.isPositive = false;
  return c;
  }
}

largeInteger largeInteger::addAbsValue(const largeInteger& a, const largeInteger& b)
{
	int digitsResult,i;
	int tempInt = 0, count = 0;
	largeInteger c;
			
	if ( a.numberOfDigits < b.numberOfDigits ) digitsResult = b.numberOfDigits + 1;
	else digitsResult = a.numberOfDigits + 1;

	int* temp = new int[digitsResult];
	
	while ( tempInt == 1 || count < digitsResult )
	{
	if ( count < b.numberOfDigits && count < a.numberOfDigits )
	tempInt += b.number[count] + a.number[count];
	else if ( count < b.numberOfDigits )
	tempInt += b.number[count];
	else if ( count < a.numberOfDigits)
	tempInt += a.number[count];
	
	if ( tempInt <= 9 ) 
	{
		temp[count] = tempInt; tempInt = 0;
	}
	else 
	{
		temp[count] = tempInt % 10; tempInt = 1;
	}
	count++; 
	}
	
	if (temp[count - 1] == 0) digitsResult--;

	delete []c.number;
	c.numberOfDigits = digitsResult;
	c.number = new int[digitsResult];
	c.isPositive = true;
	
	for ( i=0; i < (digitsResult); i++) c.number[i] = temp[i];

	delete []temp;
 	return c;

}

largeInteger largeInteger::add(const largeInteger& a,const largeInteger& b)
{
  
  if ( a.isPositive == b.isPositive )
  {		
		largeInteger c(addAbsValue(a,b));
		c.isPositive = a.isPositive;
		return c;
	}
  else
  {
	 
		 if (isAbsFirstGreaterOrEqualSecond(a,b))
		 {
				largeInteger c(subtractAbsFirstFromSecond(a,b));  
				c.isPositive = a.isPositive;
				return c;
		 }
		 else
		 {
				largeInteger c(subtractAbsFirstFromSecond(b,a));
				c.isPositive = b.isPositive; 
				return c;
		 }

	
	}
  
}

largeInteger largeInteger::sub(const largeInteger& a,const largeInteger& b)
{
  
 if (a.isPositive == b.isPositive)
 {
	 if (isAbsFirstGreaterOrEqualSecond(a,b))
	 {
		largeInteger c(subtractAbsFirstFromSecond(a,b));	
    c.isPositive = a.isPositive;
	  return c;
	 }
	 else
	 {
	  largeInteger c(subtractAbsFirstFromSecond(b,a));	
    c.isPositive = !(b.isPositive);
	  return c;
	 }

 }
 else
 {
   if (a.isPositive == true && b.isPositive == false)
   {
		 largeInteger c(addAbsValue(a,b));
		 c.isPositive = a.isPositive;
		 return c;
	 }
   else
   {
		 largeInteger c(addAbsValue(a,b));
		 c.isPositive = a.isPositive;
	   return c;
	 }
	 
 }
  
}

int largeInteger::getSize() const {  return numberOfDigits; }

void largeInteger::print() const
{
	// numbers are stored in reverse order
	if (!isPositive) std::cout <<'-';
	
	for (int i=0;i<numberOfDigits;i++)
	{
		std::cout << number[numberOfDigits - i - 1];
	}
  std::cout << std::endl;
}

void largeInteger::set(const largeInteger x)
{
  delete []number;
  number = new int[x.numberOfDigits];
  for (int i=0;i<x.numberOfDigits;i++) number[i] = x.number[i];
  numberOfDigits = x.numberOfDigits;
  isPositive = x.isPositive;
}

void largeInteger::set(std::string s)
{
	delete[]number;
	number = new int[s.size()];
	parseStringAndStoreInNumber(s);
}

void largeInteger::parseStringAndStoreInNumber(std::string s)
{
	isPositive = true;
	numberOfDigits = 0;
			
	for ( int i=0; i < static_cast<int>(s.size()); i++ )
	{
		//negative number
		if ( s[i] == 45 && i == 0) 
		{
		  isPositive = false;
		  continue;
		}
		// plus sign - positive - ignore
		if ( s[i] == 43 && i == 0) continue;
		if ( s[i] < 48 || s[i] >57) std::cout << "Invalid character. should be between 0 and 9; " << std::endl;
				
		// convert ascii code to int; code for zero is '48'
		number[s.size() - i - 1] = (s[i] - 48);
		numberOfDigits++;
	}

}

void largeInteger::borrowOne(int *n, int position)
{
  n[position] += 10;
 	
	while ( n[position + 1] == 0 )
	{
	  n[position + 1] += 9;	
		position++;
	}
	
	n[position + 1] -= 1;
	
}

largeInteger largeInteger::subtractAbsFirstFromSecond(const largeInteger&a, const largeInteger& b)
{
  largeInteger c(a);

  int *temp = new int[c.numberOfDigits];
  int i,j;
  int zeroesToTheLeft = 0;
  bool isResultZero = true;
      
  for (i=0;i < b.numberOfDigits;i++)
  {
		if ( c.number[i] >= b.number[i] )
		{
			temp[i] = c.number[i] - b.number[i];
			if ( c.number[i] != b.number[i] ) isResultZero = false;
		}
		else
		{
			borrowOne(c.number,i); 
			temp[i] = c.number[i] - b.number[i];
			isResultZero = false;
		} 
  }

  if (!isResultZero)  
  {
		for (j=i; j< c.numberOfDigits;j++)
		{
			temp[j] = c.number[j];
		} 
		i = c.numberOfDigits - 1;
		
		while ( temp [i] == 0 )
		{
		zeroesToTheLeft++;
		i--;
		}
    
    delete []c.number;
    c.number = new int[c.numberOfDigits - zeroesToTheLeft];
    for ( i=0; i < (c.numberOfDigits - zeroesToTheLeft); i++) c.number[i] = temp[i];
		c.numberOfDigits = c.numberOfDigits - zeroesToTheLeft;
  }
  
  else
  
  {
		delete []c.number;
		c.number = new int[1];
		c.number[0] = 0;
		c.numberOfDigits  = 1;
  }

  delete []temp;
  return c;
  
}

bool largeInteger::isAbsFirstGreaterOrEqualSecond(const largeInteger& a, const largeInteger& b)
{
	
	if ( a.numberOfDigits > b.numberOfDigits ) return true;
	else if ( a.numberOfDigits < b.numberOfDigits ) return false;
	else if ( a.numberOfDigits == b.numberOfDigits )
	     {
					for (int i = a.numberOfDigits - 1 ; i >= 0; i--)
					{
					if ( a.number[i] > b.number[i] ) return true;
					if ( a.number[i] < b.number[i] ) return false;
					}

			 }
	
	return true;
	
}

largeInteger::largeInteger() 
{  
	number = new int[1];
	parseStringAndStoreInNumber("0"); 
}

largeInteger::largeInteger(std::string s) 
{  
  number = new int[s.size()];
	parseStringAndStoreInNumber(s); 
}

largeInteger::largeInteger(const largeInteger& otherObject)
{
	numberOfDigits = otherObject.numberOfDigits;
	number = new int[otherObject.numberOfDigits];
	for (int i=0;i<otherObject.numberOfDigits;i++) number[i] = otherObject.number[i];
	isPositive = otherObject.isPositive;
}

largeInteger::~largeInteger() {  	delete []number;  }


int main(int argc, char **argv)
{
 // test constructors and set / get 
 largeInteger a,b,c,d;
 
 a.print();
 b.print();
 c.print();
 d.print();

 largeInteger e("999"),f("9999"),g("99999"),h("999999"),m("23333333333333333333333333333333339");

 e.print();
 f.print();
 g.print();
 h.print();
 m.print();

 
 e.set(m);
 e.print();
 e.set("9876543210");
 e.print();
 std::cout << "number of digits last number is : " << e.getSize() << std::endl;
  
 a.set("100");
 b.set("99");
 c.set("1");
 a.add(a,b);
 c.print();
 
 a.set("5000000000000000000000000");
 b.set("99");
 c.set("1");
 
 //c = a.add_v2(a,b);
 //c.print();
 
 largeInteger teste1(a.add(c,a));
 teste1.print();
 
 largeInteger teste2(a.add(a,c));
 teste2.print(); 
 
 a.set("5");
 b.set("-10");
 
 largeInteger teste3(a.add(a,b));
 teste3.print();
 a.print();
 std::cout <<"number of digits a "<<a.getSize()<< std::endl;
 b.print();
 std::cout <<"number of digits b "<<b.getSize()<< std::endl;
 teste3.print();
 std::cout << "numberofdigits teste3 " << teste3.getSize() << std::endl;
 
 // class largeInteger not overloaded with '='
 //largeInteger teste4;
 //teste4 = teste4.add(a,b);
 //teste4.print();
 
 a.set("99");
 b.set("33");
 
 largeInteger teste5(a.sub(a,b));
 teste5.print();
 
 largeInteger teste6(a.sub(b,a));
 teste6.print();
 
 largeInteger teste7(a.add(a,b));
 teste7.print();

 a.set("5633333333333333333333333333333333333333486");
 b.set("9044444444444444444444444444343434343434343434334343434344444444444444444444343434333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333");
 largeInteger teste8(a.mult(a,b));
 teste8.print();

}

