import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Iterator;
import java.util.Scanner;

//This class provides all the logic and function
public class Shop {
    private ArrayList<Item> ItemList;
    private Scanner sc = new Scanner(System.in);

    public Shop() {
        System.out.println("New Shop for Items created.");
        ItemList = new ArrayList<Item>();
    }

    public int getSize() {
        return ItemList.size();
    }
    //Search the item id
    private Item search(long code) {
        Iterator<Item> itr = ItemList.iterator();
        Item item;
        while (itr.hasNext()) {
            item = new Item(itr.next());
            if (item.getCode() == code) {
                return item;
            }
        }
        return null;
    }
    //Search the item name
    public Item search(String name) {
        Iterator<Item> itr = ItemList.iterator();
        Item item;
        while (itr.hasNext()) {
            item = new Item(itr.next());
            if (item.getName() == name) {
                return item;
            }
        }
        return null;
    }
    //Adds an item
    public void addItem() {
        long aCode;
        String aName;
        double aPrice;
        int aQuantity;
        Item foundItem;

        System.out.println("Enter Item code:");
        aCode = sc.nextLong();
        foundItem = search(aCode);
        if (foundItem == null) {
            System.out.println("Item name : ");
            aName = sc.next();
            System.out.println("Price : ");
            aPrice = sc.nextDouble();
            System.out.println("Quantity : ");
            aQuantity = sc.nextInt();
            Item aItem = new Item(aName, aPrice, aCode, aQuantity);
            ItemList.add(aItem);
        } else if (foundItem != null) {
            System.out.println("Item exists");
        }

    }
    //Update the quantity
    public void updateStock() {
        int choice, quantity;
        long code;
        double price;
        Item foundItem;

        System.out.println("1. Update quantity.");
        System.out.println("2. Update price.");
        System.out.println("Choice:");
        choice = sc.nextInt();

        System.out.println("Enter Item code:");
        code = sc.nextLong();
        foundItem = search(code);
        if (foundItem == null) {
            System.out.println("Item not found");
            return;
        }

        if (choice == 1) {

            System.out.println("Enter quantity to add: ");
            quantity = sc.nextInt();
            foundItem.setQuantity(foundItem.getQuantity() + quantity);
            System.out.println("\n Quantity updated\n");
            System.out.println("Present quantity: " + foundItem.getQuantity());
        }

        else if (choice == 2) {

            System.out.println("Enter new price: ");
            price = sc.nextDouble();
            foundItem.setPrice(price);
            System.out.println("\n Price updated\n");
            System.out.println("Present Price: " + foundItem.getPrice());
        }

        else {
            System.out.println("Wrong choice!!");
            updateStock();
        }

    }
    //Display the item information
    public void display() {

        long code;
        Item foundItem;

        System.out.println("Enter Item code:");
        code = sc.nextLong();
        foundItem = search(code);
        if (foundItem == null) {
            System.out.println("Item not found");
            return;
        }

        System.out.println(foundItem.toString());
    }
    //Simulates a purchase
    public void purchaseItem() {
        int numberOfItem;
        long code;
        Item foundItem;

        System.out.println("Enter Item code:");
        code = sc.nextLong();
        foundItem = search(code);
        if (foundItem == null) {
            System.out.println("Item not found");
            return;
        }

        System.out.println("Number of Item : ");
        numberOfItem = sc.nextInt();
        if (numberOfItem > foundItem.getQuantity()) {
            System.out.println("\nRequired number of Items not in stock\n\n");
            return;
        }

        else {
            System.out.println("\nCost of " + numberOfItem + " items : $. "
                    + numberOfItem * foundItem.getPrice());
            foundItem.setQuantity(foundItem.getQuantity() - numberOfItem);
        }
    }
    //Checks the item price
    public double checkPrice(long code) {
        Item foundItem = search(code);
        if (foundItem == null) {
            System.out.println("Item not found");
            return 0.0;
        }

        else
            return foundItem.getPrice();
    }
}