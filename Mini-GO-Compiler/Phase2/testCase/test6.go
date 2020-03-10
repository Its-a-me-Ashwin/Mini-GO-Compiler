package main


func main() {
	int sum := 1;
	switch (sum)
	{
		case 1: break
	}
	for (sum < 1000) 
	{
		sum += sum;
	}
	fmt.Println("%d",sum);
}

