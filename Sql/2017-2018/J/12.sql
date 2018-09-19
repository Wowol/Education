--ZAD12

select table_name, pg_total_relation_size(table_name) from information_schema.tables WHERE table_schema = 'public' AND table_type = 'BASE TABLE'
