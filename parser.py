import sys
import xml.dom.minidom as md
import mysql.connector

ROOT_DIR = #directory here
main_dict = {}
for j in range(1,3):
    directory = sys.argv[j]
    main_dict[directory] = {}
    for i in range(1,26):
        main_dict[directory][i] = {}
        doc = md.parse(ROOT_DIR+directory+'/'+str(i)+'.xhtml')
        nF, name = 0, 0
        dF, description = 0, 0
        iF, img_url = 0, 0
        rvF, review_score = 0, 0
        rcF, num_reviews = 0, 0
        pF, price = 0, 0
        local_img_url = 1
        if directory == 'metroswimshop':
      	    elements = doc.getElementsByTagName('meta')
      	    for e in elements:
      	    	if nF == dF == iF == pF == 1:
      	    	    break
      	    	if e.getAttribute('property') == 'og:description':
      	    	    if dF == 1:
      	    	        continue
      	    	    description = e.getAttribute('content')
      	    	    dF += 1
      	    	elif e.getAttribute('property') == 'og:title':
      	    	    if nF == 1:
      	    	    	continue
      	    	    name = e.getAttribute('content')
      	    	    nF += 1
      	    	elif e.getAttribute('property') == 'og:image:secure_url':
      	    	    if iF == 1:
      	    	        continue
      	    	    img_url = e.getAttribute('content')
      	    	    iF += 1
      	    	elif e.getAttribute('property') == 'product:price:amount':
      	    	    if pF == 1:
      	    	        continue
      	    	    price = e.getAttribute('content')
      	    	    pF += 1
      	    # review_element not available on this website
      	    
        elif directory == 'swim2000':
            price_element = doc.getElementsByTagName('span')
            for e in price_element:
                if e.getAttribute('class') == 'prod-price red':
                    price = e.firstChild.nodeValue
                    break

            name_element = doc.getElementsByTagName('h1')
            for e in name_element:
                if e.getAttribute('id') == 'prod-displ-name':
                    name = e.firstChild.nodeValue
                    break

            descrip_image_element = doc.getElementsByTagName('meta')
            n = 0
            for e in descrip_image_element:
                if e.getAttribute('itemprop') == 'description':
                    description = e.getAttribute('content')
                    n += 1
                elif e.getAttribute('itemprop') == 'image':
                    img_url = e.getAttribute('content')
                    n += 1
                if n == 2:
                    break

            n = 0
            reviews_element = doc.getElementsByTagName('span')
            for e in reviews_element:
                if e.getAttribute('class') == 'stars':  
                    for s_e in e.childNodes:
                        if s_e.getAttribute('class') == 'fa fa-star':
                            n += 1
                    break
            review_score = n
            num_reviews_element = doc.getElementsByTagName('p')
            num_reviews = ''
            for e in num_reviews_element:
                if e.getAttribute('class') == 'clearfix':
                    loc = e.childNodes[-1].nodeValue.find('Review')
                    if e.childNodes[-1].nodeValue[loc-3] != '\t':
                        num_reviews += e.childNodes[-1].nodeValue[loc-3]
                    num_reviews += e.childNodes[-1].nodeValue[loc-2]
                    break
        
        
        print(img_url)
        if price.find('-') != -1:
            price = price[0:price.find('-')]
        if price[0] == '$':
            price = float(price[1:]) if len(price)>1 else 0
        
        main_dict[directory][i] = {
        		 'prod_id': directory+str(i),
                        'name': name,
                        'description': description,
                        'price': price,
                        'img_url': img_url,
                        'local_img_url': local_img_url,
                        'review_score': review_score,
                        'num_reviews': num_reviews}


for i in ('swim2000','metroswimshop'):
    for j in range(1,26):
        print(main_dict[i][j]['img_url'])
        
var = ['prod_id','name', 'description', 'price', 'img_url', 'local_img_url', 'review_score', 'num_reviews']

def insert(cursor, inputs): # inputs is main_dict[i][j]
    query = 'INSERT INTO products(prod_id,name,description,price,img_url,local_img_url,review_score,num_reviews) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)'
    cursor.execute(query, inputs)

try:
    #change sql username, password, and database to use
    cnx = mysql.connector.connect(host='localhost', user='sql_user', password='sql_password', database='sql_database_to_use')
    cursor = cnx.cursor()
    cursor.execute('USE sql_database_to_use')
    cursor.execute('CREATE TABLE products(prod_id VARCHAR(16), name VARCHAR(256), description VARCHAR(4096), price DECIMAL(5, 2), img_url VARCHAR(256), local_img_url VARCHAR(256), review_score DECIMAL(2, 1), num_reviews DECIMAL(4, 1), PRIMARY KEY (prod_id))')
    
    for i in ('swim2000','metroswimshop'):
        for j in range(1,26):
            l = []
            for x in var:
                l.append(main_dict[i][j][x])
            insert(cursor, tuple(l))
            cnx.commit()
            
    cursor.close()
    
except mysql.connector.Error as err:
    print(err)
finally:
    try:
        cnx
    except NameError:
        pass
    else:
        cnx.close()
