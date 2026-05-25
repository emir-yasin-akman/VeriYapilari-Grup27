# Aşama 1: C kodunu derle ve çalıştır
FROM gcc:latest AS builder
WORKDIR /app
COPY . .
# Her şeyi Makefile üzerinden derle
RUN make
# C uygulamasını çalıştır ve graph_data.json dosyasını oluştur
RUN ./app

# Aşama 2: Python (API) ortamını kur
FROM python:3.9-slim
WORKDIR /app
RUN pip install fastapi uvicorn
COPY api.py .
# Sadece üretilen JSON dosyasını builder aşamasından al
COPY --from=builder /app/graph_data.json .

# API'yi başlat
CMD ["uvicorn", "api:app", "--host", "0.0.0.0", "--port", "8000"]