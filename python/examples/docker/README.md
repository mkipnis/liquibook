To build the container
---
docker build -t liquibook:latest -f Dockerfile .

To run it
---
docker run -d -p 8050:8050 liquibook:latest
