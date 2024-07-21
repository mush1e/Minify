# Minify URL Shortener

## Overview

Minify is a URL shortener application with a frontend built using HTMX and a backend implemented in C++. The backend includes a custom-built thread pool for handling multiple requests concurrently and an LRU cache to store and quickly access recently used URLs.

## Features

- **URL Shortening:** Converts long URLs into shorter, easily shareable links.
- **LRU Cache:** Caches recently used URLs to improve performance.
- **Thread Pool:** Handles multiple requests simultaneously for better scalability.

## Prerequisites
- C++ Compiler (e.g., g++)
- Make

## Steps
- Clone the repository:


  - ```git clone https://github.com/yourusername/minify.git```

- Build the backend:

  - ```make```
- Run the server:

  - ```./server```
- Access the frontend:
  - Open your web browser and navigate to ```http://localhost:8080```

## Usage

- Open the Minify application in your web browser.
- Enter the URL you want to shorten in the input field.
- Click the "Shorten URL" button.
- The shortened URL will be displayed below the input field and can be copied or redirected to.
- Redirecting using a Minified URL
- Copy the shortened URL.
= Paste it into your browser's address bar and hit enter.
= You will be redirected to the original URL.

## Contributing

- Fork the repository.
- Create a new branch (git checkout -b feature-branch).
- Make your changes and commit them (git commit -am 'Add new feature').
- Push to the branch (git push origin feature-branch).
- Open a pull request.
