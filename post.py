import requests


url = 'http://www.baidu.com'

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163 Safari/535.1"
}

free_proxy = {'http': 'http://124.42.7.103:80'}/#python3.6后一定要这么做

response = requests.get(url, headers=headers, proxies=free_proxy)

print(response.status_code)