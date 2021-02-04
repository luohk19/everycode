import urllib.request


def handler_opener():
    url = "http://www.baidu.com"
    handler = urllib.request.HTTPHandler()
    opener = urllib.request.build_opener(handler)
    response = opener.open(url)
    data = response.read()
    print(response)
    print(data)


handler_opener()
