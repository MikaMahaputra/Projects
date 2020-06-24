import java.util.Scanner;
//Driver class, used to run the program
public class main {
	//Main function
	public static void main(String args[]) {
        long code;
        char choice;
        Shop aShop = new Shop();
        Scanner sc = new Scanner(System.in);

        System.out.println("-----ITEM------");
        do {
            System.out.println("1. Add items to list");
            System.out.println("2. Update item list");
            System.out.println("3. Make a purchase");
            System.out.println("4. Display item details");
            System.out.println("5. Check price for a item");
            System.out.println("6. Exit");
            System.out.println("Choice:");
            choice = sc.nextLine().charAt(0);
            switch (choice) {
            case '1':
            	//Calls the function in shop class to add an item
                aShop.addItem();
                break;

            case '2':
            	//Calls the function in shop class to update the stocks
                aShop.updateStock();
                break;

            case '3':
            	//Calls the function in shop class to purchase an item
                aShop.purchaseItem();
                break;

            case '4':
            	//Calls the function in shop class to display item information
                aShop.display();
                break;

            case '5':
            	//Calls the function in shop class to see the price
                System.out.println("Price of the Item is:"
                        + aShop.checkPrice(inputCode()));

            case '6':
            	//Exits the program
                System.out.println("Thank you!\n");
                break;
            }
        } while (choice != '6');
        System.out.println("Hope you enjoyed it!");
        sc.close();
    }

    public static long inputCode() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Item code:");
        if (sc.hasNextLong()) {
            return sc.nextLong();
        } else {
            System.out.println("Invalid Input");
            return 0;
        }

    }
}
