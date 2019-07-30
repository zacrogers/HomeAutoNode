'''
	Controller for wifi arduino power outlet node

	Toggle relays on and off
	Get temperature from sensor in unit
'''
from bs4 import BeautifulSoup
import requests

class home_node:
	def __init__(self, ip, name, num_relays = 4):
		self.ip = ip
		self.name = name
		self.num_relays = num_relays

	#Set relay based on old arduino code
	def set_relay_old(self, relay_num):
		try:
			requests.get('http://{}/relay{}'.format(self.ip, relay_num))

		except requests.exceptions.RequestException as e:	
			print (e)

	''' Set relay state '''
	def set_relay(self, relay_num, state):
		try:
			requests.get('http://{}/re{}_{}'.format(self.ip, relay_num, state))

		except requests.exceptions.RequestException as e:	
			print (e)

	''' Get temperature from node '''
	def get_temp(self):
		text = "NC"
		try:
			temp = requests.get('http://'+self.ip+'/get_temp', timeout=3)
			if temp.status_code == 200:
				soup = BeautifulSoup(temp.text, 'html.parser')
				text = 'Inside: {}\u2103'.format(soup.text.strip())

		except requests.exceptions.RequestException as e:	
			print (e)

		return text		
