        if(array_len == 4)
        {
            // First check if product exists in product.txt
            int product_exists = 0;
            for(int i = 0; i < len_product; i++)
            {
                if(strcmp(record.product_id, product_id[i]) == 0)
                {
                    product_exists = 1;
                    break;
                }
            }
            
            if(!product_exists)
            {
                printf("Error: Product ID not found in product database.\n");
                continue;
            }

            // Then check if product has any records
            data_record(record_data, &len_record);
            int has_records = 0;
            
            // Check if product exists in records
            for(int i = 1; i < len_record; i++)  // Start from 1 to skip header
            {
                if(strcmp(record_data[i][1], record.product_id) == 0)
                {
                    has_records = 1;
                    break;
                }
            }

            // For new products (no records), only allow restock
            if(!has_records && choice != 1)