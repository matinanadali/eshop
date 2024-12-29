**Important**: To run the program, navigate to the root directory of the project and execute:
```bash
make run 
```
This will run the program using the default command-line arguements: `./files/categories.txt ./files/products.txt ./files/users.txt`, as specified in the Makefile.
**Important**: If you create a new .cpp file, don't forget to add the corresponding .o file to the Makefile.

# Done 28/21
-	Organized input-reading code to General.cpp
-	Added storeProducts() function to store products to the given file at the end of each session
-	Implemented admin.editProduct(), admin.removeProduct(), admin.unavailableProduct(), admin.top5Products()
	-	To track the number of orders each product appears in, I created a set called productsByOrder (TODO: find a proper name). This set stores pairs in the format {numberOfOrders, product}, where numberOfOrders represents how many orders the product is part of.
	Initially, in the Eshop constructor, this set is populated with all products, each starting with numberOfOrders set to 0. The values will be updated later as we process the customers' order histories and count the occurrences of each product in those orders. When a customer completes an order, the numberOfOrders should be updated for all products in that order.

# Done - To Do
-	[x] Initialize eshop from files
-	[x] Add user authentication
-	[x] Implement administrator functionalities
	-	[x] Add products
	-	[x] Edit products 
	-	[x] View statistics (e.g. out of stock products, products with the highest demand (see assignment))
-	[ ] Implement customer functionalities
	-	[ ] Add to cart
	-	[ ] Edit cart
	-	[ ] Complete order
	-	[ ] View order history
-	[ ] Implement product search (by title, category etc. (see assignment))
-	[ ] Store data after each session
	-	[ ] Save data to files when program terminates
	-	[ ] Extend Eshop initialization to retrieve all user/product data (orders, cart..)
-	[ ] Bonus Part

