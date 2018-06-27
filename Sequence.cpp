#include "Sequence.h"
#include<string>
Sequence::Sequence(string fn)
{
	filename = fn;
	ifRead = false;
}

string Sequence::getFilename()
{
	return filename;
}

void Sequence::read()
{
	cout << "please input the file address: ";
	string fileAddress;
	cin >> fileAddress;
	ifstream input(fileAddress, ios::in);
	int count = 0;
	if (!input)
	{
		cerr << "the file cannot be opened";
		exit(EXIT_FAILURE);
	}
	char temp;
	while (!input.eof())
	{
		input >> temp;
		if (temp!='/n')
		{
			fileData[count] = temp;
			count++;
		}
	}
	fLength = count - 1;
	ifRead = true;
}

int Sequence::length()
{
	if (ifRead) return fLength;
	else 
	{
		read();
		return fLength;
	}
	
}

int Sequence::number(char base)
{
	int count = 0;
	if (base=='A'||base=='G'||base=='C'||base=='T')
	{
		if (ifRead)
		{
			for (size_t i = 0; i < fLength; i++)
			{
				if (fileData[i] == base)count++;
			}
		}
		else
		{
			cout << "please input the file address: ";
			string fileAddress;
			cin >> fileAddress;
			ifstream input(fileAddress, ios::in);
			if (!input)
			{
				cerr << "the file cannot be opened";
				exit(EXIT_FAILURE);
			}
			char temp;
			int fDataCount = 0;
			while (!input.eof())
			{
				input >> temp;
				if (temp == base)count++;
				if (temp != '/t')
				{
					fileData[fDataCount] = temp;
					fDataCount++;
				}
			}
			fLength = fDataCount - 1;
			if (fileData[fLength-1] == fileData[fDataCount-1])count--;
			ifRead = true;
		}
		return count;
	}
	else
	{
		cout << "please input the right letters";
		return -1;
	}
}

string Sequence::longestConsecutive()
{
	int count = 1;
	int maxcount = 1;
	char base;
	if (ifRead)
	{
		for (size_t i = 0; i < fLength-1; i++)
		{
			if (fileData[i]==fileData[i+1])count++;
			else 
			{
				if (count>maxcount)
				{
					maxcount = count;
					base = fileData[i - 1];
				}
				count = 1;
			}
		}
	}
	else
	{
		cout << "please input the file address: ";
		string fileAddress;
		cin >> fileAddress;
		ifstream input(fileAddress, ios::in);
		if (!input)
		{
			cerr << "the file cannot be opened";
			exit(EXIT_FAILURE);
		}

		char prev = 'a';
		char next;
		while (!input.eof())
		{
			input >> next;
			if (next!='/t')
			{
				if (next == prev)count++;
				else
				{
					if (count>maxcount)
					{
						maxcount = count;
						base = prev;
					}
					count = 1;
				}
				prev = next;
			}
		}
	}
	char *a = new char[maxcount + 1];
	for (size_t i = 0; i < maxcount; i++)
	{
		a[i] = base;
	}
	a[maxcount] = '\0';
	string b = a;
	delete[]a;
	return b;
}

string Sequence::longestRepeated()
{
	return string();
}
