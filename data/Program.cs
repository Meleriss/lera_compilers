function int test(int f, int a)
{
	int buf = 4;
	char ch = 'a';
	// int[] arr = new int[5];
	int arr = new int(5);
	arr[3] = 3;
	// char[] arr2 = new char[5];
	char arr2 = new char(5);
	if (arr[3] - 3) {
		char test;
		f = 3;
		outputStr("test");
	}
	return 4 + arr[2] *a;
	// return 4 + 4 * 3;
}

function int cout_iter(int a)
{
	return a + 1;
}

function int Main()
{
	int f = 6;
	int a = f + -4;

	test(4, f + -4);

	// a = ((-f || test(4, -f + -4)) + -4 == 3) * 3;
	// a = f + 3;
	
	int b = 5;
	a = ((b < 4) + -4 < 3) * 3;
	outputInt(a);

	// int i = cout_iter(2);
	int i = 0;
	while (i < 5) {
		outputStr("loop");
		outputInt(i);
		i = i + 1;
	}

	int cond = 2;
	if (cond >= 2) {
		outputStr("true");
	}

	// outputStr("test");
	// outputInt(3);
	// outputInt(b + b);
	// char ch = 'd';
	// ch = 'b';
	// outputChar(ch);

	return 0;
}