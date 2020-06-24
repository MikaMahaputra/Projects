//This class is used to construct all the item we needs and to also get the getter/setter
public class Item {
    private String name;
    private double price;
    private long code;
    private int quantity;
    
    //Constructor
    public Item(String name, double price, long code, int quantity) {
        this.name = name;
        this.price = price;
        this.code = code;
        this.quantity = quantity;
    }

    public Item(Item item) {
        this.name = item.name;
        this.price = item.price;
        this.code = item.code;
        this.quantity = item.quantity;

    }

    @Override
    public String toString() {
        return "Item [Name=" + name + ", Price=" + price + ", Item Code=" + code
                + ", Quantity=" + quantity + "]";
    }
    
    //Getter method for name
    public String getName() {
        return name;
    }
    
    //Setter method for name
    public void setName(String name) {
        this.name = name;
    }
    
    //Getter method for price
    public double getPrice() {
        return price;
    }
    
    //Setter method for price
    public void setPrice(double price) {
        this.price = price;
    }
    
    //Getter method for item code
    public long getCode() {
        return code;
    }
    
    //Setter method for item code
    public void setCode(long code) {
        this.code = code;
    }
    
    //Getter method for quantity
    public int getQuantity() {
        return quantity;
    }
    
    //Setter method for quantity
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
}
