import requests


url = 'http://www.baidu.com/s?'

params = {
    "wd": "美女"
}

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163 Safari/535.1"
}

response = requests.get(url, headers=headers, params=params)

data = response.content.decode()

with open("1.html", "w", encoding="utf-8")as f:
    f.write(data)