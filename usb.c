#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID			0x03EB // atmel mfr default
#define PRODUCT_ID		0x2423 // atmel vendor default

char buffer[64];
uint64_t counter = 0;

typedef struct
{
	uint8_t iface;
	uint8_t iface_alt_setting;
	uint8_t addr_ep_in;
	uint8_t addr_ep_out;
	uint8_t bInterval;
	uint8_t wMaxPacketSize;
} TRANSFER;

typedef struct
{
	libusb_device *dev;
	libusb_device_handle *handle;
	struct libusb_device_descriptor desc_dev;

	TRANSFER bulk;
	TRANSFER iso;
	TRANSFER intrpt;
} DUE_USB;

int main()
{
	libusb_init(NULL);
	libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_WARNING);

	int retval;
	libusb_device **list = NULL;
	DUE_USB due_usb;
	due_usb.dev = NULL;
	due_usb.handle = NULL;

	retval = libusb_get_device_list(NULL,  &list);

	if(retval < LIBUSB_SUCCESS)
	{
		printf("%s\n", "failed to get device list or no devices available");
		libusb_free_device_list(list, true);
		return -1;
	}

	for(uint8_t i = 0; i < retval; i++)
	{
		retval = libusb_get_device_descriptor(list[i], &due_usb.desc_dev);

		if(retval != LIBUSB_SUCCESS)
		{
			printf("%s%u\r\n", "failed to open device ", i);
			libusb_free_device_list(list, true);
			return -1;
		}

		if(due_usb.desc_dev.idVendor == VENDOR_ID &&
				due_usb.desc_dev.idProduct == PRODUCT_ID)
		{
			due_usb.dev = list[i];
			retval = libusb_open(list[i], &due_usb.handle);
			libusb_free_device_list(list, true);

			if(retval != LIBUSB_SUCCESS)
			{
				libusb_close(due_usb.handle);
				printf("%s\r\n", "failed to open vendor/product.");
				return -1;
			}

			break;
		}
	}

	retval = libusb_get_device_speed(due_usb.dev);

	if(retval != LIBUSB_SUCCESS)
	{
		printf("%s\r\n", "failed to get USB device speed.");
	}

	if(retval == LIBUSB_SUCCESS)
	{
		switch(retval)
		{
			case LIBUSB_SPEED_LOW:
				printf("%s\n", "low speed 1.5 Mbps");
				break;
			case LIBUSB_SPEED_FULL:
				printf("%s\n", "full speed 12 Mbps");
				break; case LIBUSB_SPEED_HIGH:
				printf("%s\n", "high speed 480 Mbps");
				break;
			case LIBUSB_SPEED_SUPER:
				printf("%s\n", "super speed 5 Gbps");
				break;
			case LIBUSB_SPEED_UNKNOWN:
			default:
				printf("%s\n", "unknown speed reported");
				break;
		}
	}

	retval = libusb_set_auto_detach_kernel_driver(due_usb.handle, true);

	if(retval != LIBUSB_SUCCESS)
	{
		printf("%s\r\n", "could not set up auto detach/reattach");
		return -1;
	}

	printf("%s", "USB device speed: ");

	printf("USB version: %X\n", due_usb.desc_dev.bcdUSB);
	printf("Vendor ID: %#.4X\n", due_usb.desc_dev.idVendor);
	printf("Product ID: %#.4X\n", due_usb.desc_dev.idProduct);
	printf("Version #: %X\n", due_usb.desc_dev.bcdDevice);

	// these values are offsets into the descriptor but they are empty
	//printf("%u\n", due_usb.desc_dev.iManufacturer);
	//printf("%u\n", due_usb.desc_dev.iProduct);
	//printf("%u\n", due_usb.desc_dev.iSerialNumber);

	struct libusb_config_descriptor *conf_desc = NULL;
	const struct libusb_interface *_if = NULL;
	const struct libusb_interface_descriptor *_if_desc = NULL;
	const struct libusb_endpoint_descriptor *_ep_desc = NULL;

	for(uint8_t i = 0; i < due_usb.desc_dev.bNumConfigurations; i++)
	{
		retval = libusb_get_config_descriptor(due_usb.dev, i, &conf_desc);
		//retval = libusb_get_config_descriptor_by_value(dev, i, &conf_desc);
		//retval = libusb_get_active_config_descriptor(dev, &conf_desc);

		if(retval != LIBUSB_SUCCESS)
		{
			printf("%s\r\n", "failed to get a config descriptor for device.");

			if(conf_desc != NULL)
			{
				libusb_free_config_descriptor(conf_desc);
				libusb_close(due_usb.handle);
				libusb_exit(NULL);
			}
		}

		TRANSFER *p_transfer = NULL;
		//printf("%s%u\r\n", "Configuration ", i);

		for(uint8_t j = 0; j < conf_desc->bNumInterfaces; j++)
		{
			_if = &conf_desc->interface[j];

			//printf("%s%u\r\n", "  Interface ", j);

			for(uint8_t k = 0; k < _if->num_altsetting; k++)
			{
				_if_desc = &_if->altsetting[k];

				//printf("%s%u\r\n", "    AltSetting ", k);

				for(uint8_t l = 0; l < _if_desc->bNumEndpoints; l++)
				{
					_ep_desc = &_if_desc->endpoint[l];

					//printf("%s%u\r\n", "      Endpoint ", l);

					//printf("        %s\t\t%u\n", "bLength: ",
					//		_ep_desc->bLength);
					//printf("        %s\t%u\n", "bDescriptorType: ",
					//		_ep_desc->bDescriptorType);
					//printf("        %s\t%u\n", "bEndpointAddress: ",
					//		_ep_desc->bEndpointAddress);
					//printf("        %s\t\t%u\n", "bmAttributes",
					//		_ep_desc->bmAttributes);
					//printf("        %s\t\t%u\n", "wMaxPacketSize",
					//		_ep_desc->wMaxPacketSize);
					//printf("        %s\t\t%u\n", "bInterval: ",
					//		_ep_desc->bInterval);
					//printf("        %s\t\t%u\n", "bRefresh: ",
					//		_ep_desc->bRefresh);
					//printf("        %s\t\t%u\n", "bSynchAddress ",
					//		_ep_desc->bSynchAddress);
					//printf("        %s\t\t\t%s\n", "extra: ",
					//		_ep_desc->extra);
					//printf("        %s\t\t%u\n", "extra_length: ",
					//		_ep_desc->extra_length);

					switch(_ep_desc->bmAttributes & 0x03)
					{
						case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
							p_transfer = &due_usb.iso;
							break;
						case LIBUSB_TRANSFER_TYPE_BULK:
							p_transfer = &due_usb.bulk;
							break;
						case LIBUSB_TRANSFER_TYPE_INTERRUPT:
							p_transfer = &due_usb.intrpt;
							break;
						case LIBUSB_TRANSFER_TYPE_CONTROL:
						case LIBUSB_TRANSFER_TYPE_BULK_STREAM:
						default:
							continue;
					}

					p_transfer->iface = j;
					p_transfer->iface_alt_setting = k;
					p_transfer->bInterval = _ep_desc->bInterval;
					p_transfer->wMaxPacketSize = _ep_desc->wMaxPacketSize;

					if(_ep_desc->bEndpointAddress & 0x80)
					{
						p_transfer->addr_ep_in = _ep_desc->bEndpointAddress & 0x0F;
					}

					if(!(_ep_desc->bEndpointAddress & 0x80))
					{
						p_transfer->addr_ep_out = _ep_desc->bEndpointAddress & 0x0F;
					}
				}
			}
		}

		if(conf_desc != NULL)
		{
			libusb_free_config_descriptor(conf_desc);
		}
	}

	//printf("%s\n", "Bulk: ");
	//TRANSFER *p_transfer = &due_usb.bulk;
	//printf("  Interface: %u\r\n", p_transfer->iface);
	//printf("  Alt setting: %u\r\n", p_transfer->iface_alt_setting);
	//printf("  EP In: %u\r\n", p_transfer->addr_ep_in);
	//printf("  EP Out: %u\r\n", p_transfer->addr_ep_out);
	//printf("  bInterval: %u\r\n", p_transfer->bInterval);
	//printf("  wMax: %u\r\n", p_transfer->wMaxPacketSize);
	//p_transfer++;

	//printf("%s\n", "Isochronous: ");
	//printf("  Interface: %u\r\n", p_transfer->iface);
	//printf("  Alt setting: %u\r\n", p_transfer->iface_alt_setting);
	//printf("  EP In: %u\r\n", p_transfer->addr_ep_in);
	//printf("  EP Out: %u\r\n", p_transfer->addr_ep_out);
	//printf("  bInterval: %u\r\n", p_transfer->bInterval);
	//printf("  wMax: %u\r\n", p_transfer->wMaxPacketSize);
	//p_transfer++;

	//printf("%s\n", "Interrupt: ");
	//printf("  Interface: %u\r\n", p_transfer->iface);
	//printf("  Alt setting: %u\r\n", p_transfer->iface_alt_setting);
	//printf("  EP In: %u\r\n", p_transfer->addr_ep_in);
	//printf("  EP Out: %u\r\n", p_transfer->addr_ep_out);
	//printf("  bInterval: %u\r\n", p_transfer->bInterval);
	//printf("  wMax: %u\r\n", p_transfer->wMaxPacketSize);

	retval = libusb_claim_interface(due_usb.handle, due_usb.bulk.iface);
	//retval = libusb_claim_interface(due_usb.handle, due_usb.intrpt.iface);

	if(retval != LIBUSB_SUCCESS)
	{
		printf("%s\r\n", "failed to claim interface");
		return -1;
	}

	retval = libusb_set_interface_alt_setting(due_usb.handle,
			due_usb.intrpt.iface, due_usb.intrpt.iface_alt_setting);
	retval = libusb_set_interface_alt_setting(due_usb.handle,
			due_usb.bulk.iface, due_usb.bulk.iface_alt_setting);

	if(retval != LIBUSB_SUCCESS)
	{
		printf("%s\r\n", "failed to set interface alternate setting");
		return -1;
	}

	int transferred;

	while(true)
	{
		snprintf(buffer, 100, "deadbeef: %" PRIu64, ++counter);

		libusb_bulk_transfer(due_usb.handle,
				LIBUSB_ENDPOINT_OUT | due_usb.bulk.addr_ep_out,
				(unsigned char *) buffer, 64, &transferred, due_usb.bulk.bInterval);
		
		libusb_bulk_transfer(due_usb.handle,
				LIBUSB_ENDPOINT_IN | due_usb.bulk.addr_ep_in,
				(unsigned char *) buffer, 64, &transferred, due_usb.bulk.bInterval);

	//	libusb_interrupt_transfer(due_usb.handle,
	//			LIBUSB_ENDPOINT_OUT | due_usb.intrpt.addr_ep_out,
	//			(unsigned char *) buffer, 64, &transferred, due_usb.intrpt.bInterval);

	//	libusb_interrupt_transfer(due_usb.handle,
	//			LIBUSB_ENDPOINT_IN | due_usb.intrpt.addr_ep_in,
	//			(unsigned char *) buffer, 64, &transferred, due_usb.intrpt.bInterval);

		printf("in: %s\n", buffer);

	}


	libusb_close(due_usb.handle);
	libusb_exit(NULL);
	return 0;
}

