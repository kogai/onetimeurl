APP := $(shell gcloud config get-value project -q)
VERSION := v1
NAME := $(APP)/app:$(VERSION)

.PHONY: app
app:
	docker build -t $(NAME) .
	docker tag $(NAME) gcr.io/$(NAME)

.PHONY: create
create:
	kubectl create -f app.yaml
	kubectl create -f db.yaml
	kubectl create -f cache.yaml

.PHONY: delete
delete:
	kubectl delete service --all
	kubectl delete pvc --all
	kubectl delete pod --all
	kubectl delete deploy --all

.PHONY: replace
replace:
	kubectl replace --force -f app.yaml
	kubectl replace --force -f db.yaml
	kubectl replace --force -f cache.yaml

.PHONY: set
set:
	kubectl set image deployment/app app=$(NAME)
