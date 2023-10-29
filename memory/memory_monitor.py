import psutil
import requests
import time

# Задайте пороговое значение для потребления памяти (в процентах)
memory_threshold = 90

# URL API, на который будет отправлен HTTP-запрос при превышении порога
api_url = "http://example.com/api/alarm"

while True:
    # Получите информацию о потреблении памяти
    memory_info = psutil.virtual_memory()
    used_memory_percent = memory_info.percent

    print(f"Used memory: {used_memory_percent}%")

    if used_memory_percent > memory_threshold:
        print("Memory usage exceeded the threshold. Sending HTTP request...")

        # Отправьте HTTP-запрос на API
        try:
            response = requests.post(api_url, data={"message": "Memory usage exceeded the threshold"})
            if response.status_code == 200:
                print("HTTP request sent successfully.")
            else:
                print(f"Failed to send HTTP request. Status code: {response.status_code}")
        except Exception as e:
            print(f"Failed to send HTTP request: {str(e)}")

    # Пауза перед следующей проверкой (например, каждые 5 минут)
    time.sleep(300)
