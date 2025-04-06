# E-Shop

## Execution Instructions
To run the program, make sure you're in the root directory of the project and run the following command in your terminal:
```bash
make run
```
The program will run using the parameters defined in the specifications: `./files/categories.txt ./files/products.txt ./files/users.txt`, as specified in the Makefile.
**Note:** If you create additional `.cpp` files, don’t forget to modify the Makefile by adding the corresponding `.o` file!

---

## Implementation of Basic Functions

### Administrators

Administrators can:
1. Add new products by selecting `1` from the options menu.
2. Edit any attribute of any product by selecting `2` from the options menu.
3. Search for any product by selecting `4` from the options menu.
4. a. View unavailable products by selecting `5` from the options menu.
   b. View the 5 most frequently ordered products, regardless of quantity, by selecting `6` from the options menu.

### Customers

Customers can:
1. Search for any product by selecting `1` from the options menu.
2. Add products to their cart by selecting `2` from the options menu.
3. Update the quantity of a product in their cart by selecting `3`, or remove it completely by selecting `4` from the options menu.
4. Complete their order by selecting `5` from the options menu.
5. View their order history by selecting `6` from the options menu.

---

## Classes Created

- **User Class**  
  The `User` class contains methods with common names for both administrators and customers. It serves as a base class, with the `Administrator` and `Customer` classes derived from it. This allows us to leverage polymorphism. Additionally, it contains information about each user, such as their name, password, and role. Finally, the `User` class has a pointer to the `eshop` it corresponds to. Since each user corresponds to exactly one e-shop and their actions depend directly on it, we considered it appropriate to include it as a field in the structure, so we don't have to pass it as an argument to every method in `User` that interacts with the e-shop. 

- **Administrator and Customer Classes**  
  The `Administrator` class defines the methods for administrators, while the `Customer` class defines those for customers, with the addition of some extra fields and methods for managing the shopping cart and discounts.

- **Eshop Class**  
  The `Eshop` class is the core class on which the entire e-shop is based. It stores all the users, products, product categories, and product information that help us implement functions like `top5Products`. It also contains the necessary methods for the successful login or registration of a user.

- **Product Class**  
  This class contains all the information about a product and methods for managing it.

- **Order Class**  
  An object of the `Order` class represents an order placed by a user, including the products in the order and the total cost.

---

**Note:** The way messages are displayed for the program's operation is based on the `samples` provided.

---

### The `General.cpp` File
The `General.cpp` file contains functions that, as it turned out, needed to be used in many parts of the code. For this reason, these functions are grouped together in this file so that a simple call is enough each time. It is primarily intended for validating the values read and printing appropriate error messages.

---

## User Login/Registration

Once the necessary files are loaded, the e-shop starts its operation by calling `eshop.showLoginPrompt();`.  
Depending on whether the user wants to log in or register, we proceed to the corresponding function.  
After the necessary checks for correct and valid credential entry, the appropriate options menu is displayed based on the user's role.  
Then, the user selects the function they want, and the corresponding function is called.

---

## Storing Users/Products

To store the users and products of the e-shop, we chose the `unordered_map` data structure and created two hash tables:
- `users: username -> pointer to User`
- `products: product title -> Product object`

This way, operations for insertion, deletion, and searching by username or product title have the minimal possible complexity ($O(1)$).

---

## Implementation of Detailed Software Specifications

### Administrators

1. **The `addProduct()` function**  
   After providing all the information for the product, it is added to the e-shop's product map via the `addProduct()` function.
2. **The `updateProduct()` function**  
   The administrator selects the attribute of the product they want to modify. A copy of the existing product is created, and the selected attribute is changed. Then, the product is removed from the product map via `removeProductByTitle()` and the new product is added via `addProduct()` (Note: `addProduct` in the `Eshop` class is different from the `addProduct` in the `Administrator` class defined above).
3. **The `removeProduct()` function**  
   This is a simple call to the helper function `removeProductByTitle()`.
4. **The `searchProduct()` function**  
   This function is common for both administrators and customers and is considered a function of the `User` class.  
   If the user chooses to search by product title, the product's details are displayed if it exists; otherwise, an appropriate message is printed.  
   If the user chooses to search by a specific category, the products in the requested category are found and their details are displayed.  
   If the user selects to see all products, the details of all products are printed.
5. **The `unavailableProducts()` function**  
   The quantity of each product is checked, and those with zero quantity (<10e-6) are displayed.
6. **The `top5Products()` function**  
   After getting the products with the most sales via the helper function `getTop5Products()`, we check if there are at least 5 products. If so, their details are displayed.

### Customers

1. **The `searchProduct()` function**  
   Similar to the one above.
2. **The `addProduct()` function**  
   For the product given by the customer, the quantity is checked. If it's not zero, the customer enters the desired quantity, and we check if the required stock is available, displaying an appropriate message. If the product is already in the cart, the desired quantity is added to the existing amount; otherwise, the product is simply added to the cart. Finally, the requested quantity is subtracted from the product's stock.
3. **The `updateProduct()` function**  
   After the user provides the product they are interested in, if it's in the cart, the new quantity is requested, and the cart is updated with the new quantity. If the desired quantity is not available, an appropriate message is displayed.
4. **The `removeProduct()` function**  
   After ensuring that the product exists in the cart, it is removed using the helper function `removeProductFromCart`.
5. **The `makeOrder()` function**  
   When the user completes an order, for each product in the order, the discount structures are updated, and it is checked whether the user is eligible for a discount on the current order.  
   Additionally, the order history is updated by adding the current order, and the cart is emptied.
6. **The `viewOrderHistory()` function**  
   For each order in the `orderHistory`, its order number, the quantity of each product it contains (along with the product title), and the total cost of the order are displayed.

---

## Bonus

1. If a user buys product X in 3 consecutive orders, they get a 20% discount on product X in the next order where product X is purchased.
2. If a user buys at least X quantity of products from a category in one order (where X is the minimum quantity provided), a 30% discount is applied to products from that category in the next order. If the user does not buy products from that category in the next order, the discount is lost.
3. A user's favorite product is considered the one with the highest quantity across their entire order history. To find the favorite product, we store the total quantity of each product the user has bought in a `map<product title, amount>` and use a `set<pair<amount, product title>>` to keep products sorted in descending order based on the quantity purchased. Thus, the user's favorite product is always the first element in the `set`. Every time the user makes an order, we remove each product from the order from the `set`, update its quantity accordingly, and re-add it with the updated quantity. This approach is efficient, as it allows easy updating of product quantities (requires one removal and one addition in the set → $O(logn)$) and easy access to the favorite product (first element of the set → $O(1)$).
