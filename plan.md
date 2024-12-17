# Πλάνο

### Βασικές Κλάσεις
-	Eshop
-	Customer -> User
-	Administrator -> User
-	Product
-	Order
-	
### Eshop
##### Πεδία
-	Map χρηστών για γρήγορη αναζήτηση
	Θα είναι map από pointers ώστε όταν αλλάζει ένα προϊόν να αλλάζει αυτόματα και εδώ
-	(Vector) προϊόντων
-	Active User
##### Μέθοδοι
-	fetchData - initialize
-	storeData (after each session)
-	User login/logout/register
-	addProduct, changeProduct, searchProduct(title, category, subcategory...)
	Αυτές οι μέθοδοι θα μπορούσαν να είναι και μέθοδοι του διαχειριστή αλλά θα έπρεπε να έχει πρόσβαση στα products (μέσω μίας getProducts). Για να μη γίνει αυτό, η κλάση διαχειριστής προτείνω να λειτουργεί ως η διεπαφή ανάμεσα στον χρήστη και την addProducts, δηλαδή να μαζεύει όλα τα στοιχεία του προϊόντος και να περνάει έτοιμο όρισμα Product στην addProduct. Γενικά προτείνω να το κάνουμε έτσι.. ας πούμε και η αλλαγή των προϊόντων να γίνεται μέσα από την product.changeProduct().

### User
##### Πεδία
-	Username, password
	Θα είναι map από pointers ώστε όταν αλλάζει ένα προϊόν να αλλάζει αυτόματα και εδώ
-	(Vector) προϊόντων
##### Μέθοδοι
-	searchProduct
-	viewProduct (υπάρχει και στον Administrator και στον Customer) αλλά με διαφορετικές λειτουργίες

### Administrator -> User
##### Πεδία
##### Μέθοδοι
-	addProduct, changeProduct, viewProduct

### Customer-> User
##### Πεδία
- Καλάθι αγορών: vector με pair προϊόν-ποσότητα?
- Ιστορικό παραγγελιών: vector με Orders
##### Μέθοδοι
-	addProductToCart, changeCart
-	viewProduct
-	makeOrder
-	viewOrderHistory

### Product 
##### Πεδία
-	Όλα τα πεδία που αναγράφονται στην εκφώνηση
##### Μέθοδοι
-	changeProduct

