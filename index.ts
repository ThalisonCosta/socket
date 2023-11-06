const productsList = [
  {
    "id": 1,
    "title": "Fjallraven - Foldsack No. 1 Backpack, Fits 15 Laptops",
    "price": 109.95,
    "description": "Your perfect pack for everyday use and walks in the forest. Stash your laptop (up to 15 inches) in the padded sleeve, your everyday",
    "category": "men's clothing",
    "image": "https://fakestoreapi.com/img/81fPKd-2AYL._AC_SL1500_.jpg",
    "rating": {
      "rate": 3.9,
      "count": 120
    }
  },
  {
    "id": 2,
    "title": "Samsung Galaxy S21 Ultra 5G",
    "price": 1199.99,
    "description": "Experience the power of the ultimate smartphone. Featuring a 108MP camera, 120Hz dynamic AMOLED 2X display, and 5G connectivity.",
    "category": "electronics",
    "image": "https://fakestoreapi.com/img/81fPKd-2AYL._AC_SL1500_.jpg",
    "rating": {
      "rate": 4.8,
      "count": 350
    }
  },
  {
    "id": 3,
    "title": "Levi's Men's 505 Regular Fit Jeans",
    "price": 49.99,
    "description": "Get classic style and comfort with Levi's 505 Regular Fit Jeans. Perfect for any casual occasion, these jeans are a wardrobe essential.",
    "category": "men's clothing",
    "image": "https://fakestoreapi.com/img/81fPKd-2AYL._AC_SL1500_.jpg",
    "rating": {
      "rate": 4.5,
      "count": 420
    }
  },
  {
    "id": 4,
    "title": "Sony Noise Cancelling Headphones WH1000XM4",
    "price": 299.99,
    "description": "Enjoy superior sound quality and noise cancellation with Sony WH1000XM4 headphones. Perfect for music lovers and travelers.",
    "category": "electronics",
    "image": "https://fakestoreapi.com/img/81fPKd-2AYL._AC_SL1500_.jpg",
    "rating": {
      "rate": 4.9,
      "count": 280
    }
  },
  {
    "id": 5,
    "title": "Women's Casual Loose Pocket Long Dress",
    "price": 19.99,
    "description": "Stay comfortable and stylish with this casual long dress for women. Features a loose fit and convenient pockets for everyday wear.",
    "category": "women's clothing",
    "image": "https://fakestoreapi.com/img/81fPKd-2AYL._AC_SL1500_.jpg",
    "rating": {
      "rate": 4.3,
      "count": 180
    }
  }
];

const products = {
  data: productsList,
  total: productsList.length
}


Bun.serve({
  port: 4444,
  fetch(req) {
    const { pathname } = new URL(req.url);
    const { method } = req;

    if (pathname === "/" && method === "GET") {
      return new Response("é o bun crlh");
    }
    if (pathname === "/products" && method === "POST") {

      return new Response(JSON.stringify(products))
    }
    return new Response("Not Found!")
  },
});

