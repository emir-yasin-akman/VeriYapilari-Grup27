from fastapi import FastAPI
from fastapi.responses import JSONResponse
from fastapi.middleware.cors import CORSMiddleware
import json
import os

app = FastAPI()

# Frontend'in (HTML/JS) bu API'ye erisimine izin vermek icin CORS ayari
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"], # Her yerden erisime acik
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/api/graph")
def get_graph_data():
    """C uygulamasinin uretecegi JSON dosyasini okuyup web'e servis eder."""
    dosya_yolu = "graph_data.json"
    
    if os.path.exists(dosya_yolu):
        try:
            with open(dosya_yolu, "r", encoding="utf-8") as f:
                data = json.load(f)
            return JSONResponse(content=data)
        except Exception as e:
            return JSONResponse(content={"error": f"JSON okuma hatasi: {str(e)}"}, status_code=500)
    else:
        return JSONResponse(content={"error": "graph_data.json bulunamadi! Once C programini calistirin."}, status_code=404)

# Uygulamayi calistirmak icin terminale: uvicorn api:app --reload